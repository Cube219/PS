// # \u000a /*
#if false /*

res = ["0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010"]
n = gets.to_i
for i in 0...n + 1
print res[i]
end

# */
// # */ \u000a /*
#endif
// # \u000a */


// # \u000a /*
#if false /*

=begin

# */
// # */ \u000a /*
#endif
// # \u000a */


/*/* Begin Swift Except */

//\u000a import java.util.Scanner;
//\u000a public class Main {
//\u000a     public static String[] res = { "0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010" };
//\u000a     public static void main(String[] args) {
//\u000a         Scanner input = new Scanner(System.in);
//\u000a         int n = input.nextInt();
//\u000a         for (int i = 0; i <= n; i++) {
//\u000a             System.out.print(res[i]);
//\u000a         }
//\u000a     }
//\u000a }

// End Swift Except */

/*/* Begin Swift Except */
//\u000a /*

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<string> res = { "0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010" };
    for(int i = 0; i <= n; ++i) {
        cout << res[i];
    }
    return 0;
}
// End Swift Except */
// */

// \u000a /*

#if !BOJ
import Foundation
let res = ["0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010"]
var n = Int(readLine()!)!
for i in 0...n{
    print(res[i], terminator:"")
}
#endif
// */

// */

// # \u000a /*
#if false /*
=end
# */
// # */ \u000a /*
#endif
// # \u000a */

