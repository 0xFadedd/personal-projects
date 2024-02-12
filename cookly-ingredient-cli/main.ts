import fs from "fs";
import * as readline from "readline";
import Fuse from "fuse.js";
import { singular } from "pluralize";

class cli {
  ingredients: Tree;
  date: Date;
  dateString: string;
  tempFileName: string;
  fuse: Fuse<any>;
  layers: Array<{ "itemName": string }>;
  fuseOptions: Fuse.IFuseOptions<any>;
  rl: readline.Interface;

  constructor() {

    this.ingredients = JSON.parse(fs.readFileSync("./terseIngredients.json", "utf-8")) as Tree;
    this.date = new Date();
    this.dateString = `${this.date.getDate()}.${this.date.getMonth() + 1}${this.date.getFullYear()}_${this.date.getHours()}:${this.date.getMinutes()}:${this.date.getSeconds()}`;
    this.tempFileName = `./temp/temp_${this.dateString}.json`;
    fs.writeFileSync(this.tempFileName, JSON.stringify(this.ingredients, null, 2));
    this.layers = []
    getAllLayers(this.ingredients.categories, this.layers)
    this.fuseOptions = {
      includeScore: true,
      shouldSort: true,
      sortFn: (a, b) => {
        if (a.score && b.score) {
          return a.score - b.score
        }
        return 0
      },
      keys: ["itemName"],
    };

    this.fuse = new Fuse(this.layers, this.fuseOptions);
    // Prompt user in console for ingredient
    this.rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });
  }



  refresh() {
    fs.writeFileSync(this.tempFileName, JSON.stringify(this.ingredients, null, 2));
    this.ingredients = JSON.parse(fs.readFileSync(this.tempFileName, "utf-8")) as Tree;
    getAllLayers(this.ingredients.categories, this.layers)
    this.fuse = new Fuse(this.layers, this.fuseOptions);
    this.addQ()
  }

  addQ() {
    this.rl.question(
      "Would you like to add a category, sub category or ingredient (A: cat/sub/ing):\nEnter N to exit and save any additions\n",
      (text) => {

        if (text === "cat" || text === "category") {
          this.addCategory();
        } else if (text === "sub" || text === "subCategory") {
          this.addSubCategory();
        } else if (text === "ing" || text === "ingredient") {
          this.addIngredient();
        } else if (text === "N") {
          done(this.ingredients)
          this.rl.close();
        } else {
          console.log("Please enter a valid option");
          this.addQ();
        }
      }
    );
  }


  async addCategory() {
    this.rl.question("What is the name of the category?\n", async (text) => {
      reset(text, this)
      if ((await this.doesItemExist(text)).doesExist) {
        console.log("Category already exists, please try again\n");
        this.addQ();
      } else {
        const category = {
          itemName: singular(text),
          subCategories: undefined,
          terseIngredients: undefined,
        };
        this.ingredients.categories.push(category)

        this.refresh()
      }
    });
  }

  async addSubCategory() {
    this.rl.question("What is the name of the parent category or sub category?\n", async (text) => {
      reset(text, this)
      const { doesExist, obj } = await this.doesItemExist(text)
      if (doesExist) {
        this.rl.question("Category exists! What is the name of the new sub category?: \n", (sub) => {
          reset(text, this)
          const newSubCategory: subCategory = {
            itemName: singular(sub),
            subCategories: undefined,
            terseIngredients: undefined
          }
          function goThroughSubCategories(subCategory: subCategory, newSubCategory: subCategory) {
            if (subCategory.itemName === singular(text)) {
              if (subCategory.subCategories != undefined) {
                subCategory.subCategories.push(newSubCategory)
              } else {
                subCategory.subCategories = [newSubCategory]
              }
              return
            }
            else if (subCategory.subCategories != undefined) {
              subCategory.subCategories.forEach((sub) => {
                if (sub.itemName === singular(text)) {
                  if (sub.subCategories != undefined) {
                    sub.subCategories.push(newSubCategory)
                  } else {
                    sub.subCategories = [newSubCategory]
                  }
                  return
                } else if (sub.subCategories != null) {
                  goThroughSubCategories(sub, newSubCategory)
                } else {
                  return
                }
              })
            } else {
              return
            }
          }
          const itemToChange = findParentObject(this.ingredients.categories, obj.itemName)
          if (itemToChange != undefined) {
            goThroughSubCategories(findParentObject(this.ingredients.categories, obj.itemName), newSubCategory)
          }
          this.refresh()
        })
      } else {
        console.log("Category does not exist, please try again");
        this.addQ();
      }
    });
  }

  async addIngredient() {
    this.rl.question("What is the name of the sub category?\n", async (text) => {
      reset(text, this)
      const subCatQ = await this.doesItemExist(text)

      if (subCatQ.doesExist) {
        this.rl.question("Item exists! What is the name of the new food you want to add?\n", async (ing) => {
          reset(text, this)
          const { doesExist, obj } = await this.doesItemExist(ing)
          if (doesExist) {
            console.log(`Item already exists: ${obj.itemName}, please try again\n`);
            this.addQ();
          }
          const ingredient: terseIngredient = {
            itemName: singular(ing),
            terseName: "",
            terseIngredients: undefined
          }
          this.rl.question("What is the terse name of the ingredient?\n", (terse) => {
            reset(text, this)
            ingredient.terseName = terse

            function goThroughSubCategories(subCategory: subCategory, newIngredient: terseIngredient) {
              if (subCategory.itemName === subCatQ.obj.itemName) {
                if (subCategory.terseIngredients != undefined) {
                  subCategory.terseIngredients.push(newIngredient)
                } else {
                  subCategory.terseIngredients = [newIngredient]
                }
                return
              }
              else if (subCategory.subCategories != undefined) {
                subCategory.subCategories.forEach((sub) => {
                  if (sub.itemName === singular(text)) {
                    if (sub.terseIngredients != undefined) {
                      sub.terseIngredients.push(newIngredient)
                    } else {
                      sub.terseIngredients = [newIngredient]
                    }
                    return
                  } else if (sub.terseIngredients != null) {
                    goThroughSubCategories(sub, newIngredient)
                  } else {
                    return
                  }
                })
              } else {
                return
              }
            }

            // getLayerNumber(obj, ingredient)
            const itemToChange = findParentObject(this.ingredients.categories, subCatQ.obj.itemName)
            if (itemToChange != undefined) {
              goThroughSubCategories(findParentObject(this.ingredients.categories, subCatQ.obj.itemName), ingredient)
            }

            this.refresh()
          })
        })
      } else {
        console.log("Category does not exist, please try again\n");
        this.addQ();
      }
    });
  }

  doesItemExist(item: string): Promise<{ doesExist: boolean, obj: any }> {
    return new Promise((resolve, reject) => {
      const results = this.fuse.search(item)
      var doesExist = false
      var matchedItem = {}
      const res = results[0]
      if (results.length > 0) {
        if (res.score && res.score < 0.00000000000001) {
          doesExist = true
          matchedItem = res.item
          resolve({ doesExist: doesExist, obj: matchedItem });
        }
        else if (res.score && res.score > 0 && res.score < 0.5) {
          this.rl.question(`Did you mean ${res.item.itemName}? (Y/N)`, (text) => {
            if (text === "Y" || text === "y" || text === "Yes" || text === "yes" || text === "YES") {
              doesExist = true
              matchedItem = res.item
              resolve({ doesExist: doesExist, obj: matchedItem });
            } else {
              resolve({ doesExist: doesExist, obj: matchedItem });
            }
          })
        } else {
          resolve({ doesExist: false, obj: matchedItem });
        }
      } else {
        resolve({ doesExist: false, obj: matchedItem });
      }
    });
  }
}

interface Tree {
  categories: Array<subCategory>
}

interface subCategory {
  itemName: string
  subCategories: Array<subCategory> | undefined
  terseIngredients: Array<terseIngredient> | undefined
}

interface terseIngredient {
  itemName: string
  terseName: string
  // layerNumber: number
  terseIngredients: Array<terseIngredient> | undefined
}


function getAllLayers(object: any, layers: Array<Record<"itemName", string>>) {
  function isLowestTerseIngredient(o: any): o is terseIngredient {
    return o && typeof o.itemName === 'string' && typeof o.terseName === 'string' && typeof o.layerNumber === 'number' && typeof o.terseIngredients === undefined;
  }
  // function isSubCategory(o: any): o is subCategory {
  //   return o && typeof o.itemName === 'string' && === 'object' && typeof o.terseIngredients === 'object';
  // }

  function recursiveStepThroughLayers(o: any) {
    if (Array.isArray(o)) {
      o.forEach((obj) => {
        recursiveStepThroughLayers(obj)
      })
    } else if (typeof o === 'object' && o !== null) {

      layers.push(o)
      for (const v of Object.values<any>(o)) {
        recursiveStepThroughLayers(v)
      }
    }
  }

  recursiveStepThroughLayers(object)
  return layers
}



function findParentObject(arrOfObjects: any[], objectItemNameToFind: string) {
  let foundObject: any;
  arrOfObjects.forEach((obj) => {
    if (obj.itemName === singular(objectItemNameToFind)) {
      foundObject = obj;
    } else if (obj.subCategories) {
      foundObject = findParentObject(obj.subCategories, objectItemNameToFind);
    }
  });
  return foundObject;
}

function done(ingredients: any) {
  fs.writeFileSync("./terseIngredients.json", JSON.stringify(ingredients));
}

function reset(text: string, fn: any) {
  if (text === "r" || text === "reset" || text === "R" || text === "Reset") {
    fn.addQ();
  }
  return
}


function main() {
  const cliInstance = new cli();
  cliInstance.addQ();
}
main();