function removeDuplicates(nums: number[]): number {
    return nums.filter((val, index, arr) => arr.indexOf(index) ===val).length;
}