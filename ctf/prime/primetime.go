package main

import (
    "bufio"
    "fmt"
    "net"
    // "os"
    "regexp"
    "strconv"
    // "strings"
)

const (
    HOST     = "primetime.baectf.com"
    PORT     = "443"
    PASSWORD = "terminaldisc"
)

func isPrime(n int) bool {
    if n <= 1 {
        return false
    }
    for i := 2; i*i <= n; i++ {
        if n%i == 0 {
            return false
        }
    }
    return true
}

func getPrimeBelow(n int) int {
    for i := n - 1; i >= 2; i-- {
        if isPrime(i) {
            return i
        }
    }
    return -1
}

func main() {
    fmt.Println("Connecting to", HOST+":"+PORT)
    conn, _ := net.Dial("tcp", HOST+":"+PORT)
    defer conn.Close()
    fmt.Println("Connected", conn)
    r := bufio.NewReader(conn)
    w := bufio.NewWriter(conn)
    fmt.Println(r, w)

    // Password challenge/response
    line, _ := r.ReadString('\n')
    fmt.Print(line)
    w.WriteString(PASSWORD + "\n")
    w.Flush()
    fmt.Println(line, PASSWORD)
    // Welcome message
    line, _ = r.ReadString('\n')
    fmt.Print(line)
    line, _ = r.ReadString('\n')
    fmt.Print(line)

    // Now solve the challenge
    re := regexp.MustCompile(`: (\d*)`)
    fmt.Println("Solving challenge")
    for {
        line, _ = r.ReadString('\n')
        matches := re.FindStringSubmatch(line)
        if len(matches) == 0 {
            fmt.Print(line)
        } else {
            num, _ := strconv.Atoi(matches[1])
            fmt.Printf("Finding prime below: %d\n", num)
            prime := getPrimeBelow(num)
            fmt.Printf("Sending: %d\n", prime)
            w.WriteString(fmt.Sprintf("%d\n", prime))
            w.Flush()
            line, _ = r.ReadString('\n')
            fmt.Print(line)
        }
    }
}