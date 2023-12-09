package main

// too low 914569669

import (
    "fmt"
    "os"
    "bufio"
    "strconv"
    "strings"
)

func CheckError(e error) { 
    if e != nil { 
        panic(e);
    }
}

func isAllZeros(arr []int) bool {
    for _, value := range arr {
        if value != 0 {
            return false;
        }
    }
    return true;
}


func Day9(list []int) int {

    var l [][]int;
    l = append(l, list)
    for !isAllZeros(list) {  
        var tmp []int;
        for i:=1; i<len(list); i++ { 
           tmp = append(tmp, list[i]-list[i-1]);
        }
        l = append(l, tmp);
        list = tmp;
    }

    bef := 0
    for i:=len(l)-1; i>=0 ; i--{ 
        bef = bef + l[i][len(l[i])-1];
    }
    return bef;
}

func main() {
    file, err := os.Open("input/day9.txt");
    CheckError(err);
    defer file.Close();

    scanner := bufio.NewScanner(file);

    res := 0;

    for scanner.Scan() { 
        line := scanner.Text();
        s := strings.Split(line, " ");
        var list []int;
        for _, it := range s {
            e, err := strconv.Atoi(it);
            CheckError(err);
            list = append(list, e);
        }
        res += Day9(list)
    }

    fmt.Println("res : ", res);

    CheckError(scanner.Err());
}
