
	import java.util.*;
	public class GenerateTest 
	{
	static void generateTestCase(){

		Random r = new Random();
		int runs = 30; // Number of times to run the test suite
		int MAX_LEN = 5; //length of the test String
		int distinct = 4; //Number of distinct characters , The lower the value more chances of finding errors
		while(runs-->0){
			StringBuilder sb1 = new StringBuilder();
			StringBuilder sb2 = new StringBuilder();
			for(int i=0;i<MAX_LEN;i++){
				sb1.append((char)('A' + r.nextInt(distinct)));
				sb2.append((char)('A' + r.nextInt(distinct)));
			}
			//System.out.println(sb1);
			//System.out.println(sb2);
			if(sb1.toString().equals(sb2.toString()))
				continue;
				
			String ans = getAnswer(sb1.toString(), sb2.toString());   //Write your code in getAnswer function and return the smallest non shared substring
			
			if(!testAnswer(sb1.toString(), sb2.toString(), ans)){
				System.out.println("Wrong Answer");
				System.out.println(sb1 + "\n" + sb2);
				System.out.println("Wrong Output : " + ans);
			}
			else
				System.out.println("PASS");
		}
	}
	
	static boolean testAnswer(String t1 , String t2 , String ans){
		HashSet<String> set1 = new HashSet<>();
		HashSet<String> set2 = new HashSet<>();
		int l1 = t1.length();
		int l2 = t2.length();
		for(int i=0;i<l1;i++)
			for(int j=i + 1;j<=l1;j++)
				set1.add(t1.substring(i, j));

		for(int i=0;i<l2;i++)
			for(int j=i+1;j<=l2;j++)
				set2.add(t2.substring(i, j));

		int min = Integer.MAX_VALUE;
		for(String s:set1)
			min = !set2.contains(s) ? Math.min(min,s.length()) : min;

			return ans.length() == min && set1.contains(ans);
	}
	
	}