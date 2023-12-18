package mergeTwoLists

import (
	"fmt"
)

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */

type ListNode struct {
	Val  int
	Next *ListNode
}

func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
	var head, tail *ListNode
	for list1 != nil && list2 != nil {
		var node *ListNode
		if list1.Val < list2.Val {
			node = list1
			list1 = list1.Next
		} else {
			node = list2
			list2 = list2.Next
		}
		if head == nil {
			head = node
		} else {
			tail.Next = node
		}
		tail = node
	}
	if list1 != nil {
		if head == nil {
			head = list1
		} else {
			tail.Next = list1
		}
	}
	if list2 != nil {
		if head == nil {
			head = list2
		} else {
			tail.Next = list2
		}
	}
	return head
}
