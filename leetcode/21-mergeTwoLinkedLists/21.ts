

class ListNode {
    val: number
    next: ListNode | null
    constructor(val?: number, next?: ListNode | null) {
        this.val = (val === undefined ? 0 : val)
        this.next = (next === undefined ? null : next)
    }
}


function mergeTwoLists(list1: ListNode, list2: ListNode): ListNode | null {
    !(list1?.val && list2?.val) ? null : [];
    var arr: number[] = [];
    const addToArray = (list: ListNode) => {
        list?.val ? arr.push(list.val) : null;
        if (list?.next == null) {
           return;
        } else {
            addToArray(list.next);
        }
    }

    addToArray(list1);
    addToArray(list2);

    return arr.sort((a, b) => a - b).map((val) => new ListNode(val)).map((node, index, a) => {
        node.next = a[index + 1] || null
        return node
    })[0] ?? null;
};

var list1 = [].map((val) => new ListNode(val ?? null)).map((node, index, arr) => {
    node.next = arr[index + 1] || null
    return node
})
var list2 = [].map((val) => new ListNode(val ?? null)).map((node, index, arr) => {
    node.next = arr[index + 1] || null
    return node
})

console.log(mergeTwoLists(list1[0], list2[0]))