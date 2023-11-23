package main

import (
	"fmt"
	"strings"
)

func longestCommonPrefix(strs []string) string {
    if len(strs) == 0 {
        return ""
    }

    prefix := strs[0]

    for _, str := range strs {
        for strings.HasPrefix(str, prefix) == false {
            if len(prefix) == 0 {
                return ""
            }
            prefix = prefix[:len(prefix)-1]
        }
    }
    return prefix
}

func main() {
	strs := []string{"", "b"}
	fmt.Println(longestCommonPrefix(strs))
}
