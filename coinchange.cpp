/******************************************************
 ** File Name: coinchange.cpp
 ** Author : Amir Hossain, Calvin Garcia, Hector Cruz
 ** Date:  4/12/22
 ** Description: Using recursive methods to solve 3
 ** different versions of the CoinChange problem.
 ******************************************************/

//Compile using g++ -std=c++11
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVector (const vector<int> & v){
	cout <<"[";
	for (auto e:v){
		cout<< e << " ";
				
	}
		cout <<"]";


}

/* check if we can use values in L[left...right] to make a sum of value, and find
the best solution, i.e., smallest set of coins tht make this value
 @param L, first, last: specify a sub-vector where coins/values are chosen from
 @param value: the sum/value we want to make
 @pre-condition: all parameters are initialized, L[] and value are non-negative
 @post-condition: return true/false depending on the checking result, if return true,
   used vector contains coins that make up the value, with the minimul # of elements from 
   L [first...last]
*/
bool CoinChange (vector<int> & L, int first, int last, int value, vector<int> & used)
{

    if (value==0)
    {
 	used.clear();

	return true;
    }

   if (first>last) //no more coins to use
   {
	used.clear();

	return false;
   }

   if (value<0)
   {
	used.clear();

	return false;
   }

   //general case below

   vector<int> used1;
   bool ret1= CoinChange (L, first, last-1, value-L[last], used1);
   if (ret1) 
        // used1 include all values from L[first...last-1] that add up to valeu-L[last]
        used1.push_back (L[last]);
        //now: used1 include all coins used from L[first...last} that add up to value

   vector<int> used2;
   // If not using L[last]... 
   bool ret2 = CoinChange (L, first, last-1, value, used2);

   if (ret1 && ret2) {
	if (used1.size() > used2.size())
		used = used2;
	else
		used = used1;
        return true;
   } else if (ret1) {
	used = used1;
	return true;
   } else if (ret2){
	used = used2;
	return true;
   } else {
	used.clear();
	return false;
   }

  

} 

/*if a is {1,2,3}, first=0, last=2, the function shall returns a vector of the following vectors:
{}, {1}, {2}, {3}, {1,2},{1,3}, {2,3},{1,2,3}, all subsets of a[0...2].
Precondition: last-first+1>=1, i.e., there is at least one element in the a[first...last]
Note 1)if the length of a[first...last] is n, then the function should return a vector of 2n vectors
2) The order of these subsets does not need to match what�s listed here...
*/
vector<vector<int>> subsets(const vector<int>& a, int first, int last)
{
	vector<vector<int>> results;

	//base case
	if (first == last) 
	{
		vector<int> emptySet;
		results.push_back(emptySet);
		emptySet.push_back(a[first]); //set is no longer empty
		results.push_back(emptySet);
		return results;
	}
		
	//general case
	//subsets that do not include a[first]
	results = subsets(a, first + 1, last);

	//subsets that include a[first]
	int n = results.size();

	for (int i = 0; i < n; i++) 
	{
		vector<int> set = results[i];
		set.push_back(a[first]);
		results.push_back(set);
	}
	return results;
}


/* check if we can use values in L[left...right] to make a sum of value, while using K or less coins to do so
 @param L, first, last: specify a sub-vector where coins/values are chosen from
 @param value: the sum/value we want to make
 @param K: the max number of coins we want to use to generate value
 @pre-condition: all parameters are initialized, L[] and value are non-negative
 @post-condition: return true/false depending on the checking result, if return true,
   it's possible to make value using K or less coins that make up the value.
*/
bool CoinChangeK (const vector<int> & coins, int first, int last, int value, int K)
{
    //Creates vector with all subsets within a vector
	vector<vector<int>> results = subsets(coins, first, last);


	//Base Case with Anomalies in function-input
	if (K <= 0 || value <= 0 || first < 0 || last < 0 || first > last || coins.size() <= 0)
	{
		return false;
	}

	//Base case if only given 1 Coin Value Given
	if (first == last)
	{
		if (coins[first] == value)
		{
			return true;
		}
	}

	//Variable for number of coins used to compute value
	int coins_used = 0;

	//Variable for total value of each subset
	int subset_value = 0;

	//Creates vector based on subelements of the results vector of vectors
	vector <int> subelements;

	//Iterates thru each subset 
	for (int i = 0; i < results.size(); i++) 
	{
			//Ensures that subsets that are used have at least 1 element in it 
			//and are less than or equal to size K
			if (results[i].size() <= K && results[i].size() > 0)
			{
				//Sets subsetelements vector equal to the values from results[i]
				subelements = results[i];
				
					//Creates the sum of each subset
					for (int x = 0; x < subelements.size(); x++)
					{
						subset_value += subelements[x];
					}
			}	

			
			//Coins used is equal to number of subset elements
			coins_used = subelements.size();

			//Checks if current total subset value is equal to the desired value & 
			//the number of coins used is less than or equal to K
			if (subset_value == value && coins_used <= K)
			{
				//If one subset is true, break from loop
				return true;
				break;
			}

			//Resets counters for number of coins used and subset values
			coins_used = 0;
			subset_value = 0;
	}
		//Returns false if no subsets are equal to the given value or  
		//if you need more coins than given to get the desired value
		return false;
}
	
/* check if we can use values in L[left...right] to make a sum of value, and find
the best solution, i.e., smallest set of coins tht make this value, and return this smallest set of 
coins as a vector of ints called bestSolution
 @param L, first, last: specify a sub-vector where coins/values are chosen from
 @param value: the sum/value we want to make
 @pre-condition: all parameters are initialized, L[] and value are non-negative
 @post-condition: return true/false depending on the checking result, if return true,
   used vector contains coins that make up the value, with the minimum # of elements from 
   L [first...last] and also returns this bestSolution vector
*/
bool UnlimitedCoinChange(const vector<int> &coins, int value, vector<int> &bestSolution)
{
	vector<int> coin_temp;
	int count = 0;
	if (value == 0)
	{
		bestSolution.clear();
		// coin_temp.clear();
		//     printf("step 3:            ");
		return true;
	}
	if (value < 0)
	{
		bestSolution.clear();
		// coin_temp.clear();
		//  printf("step 2:            ");
		return false;
	}

	for (auto i : coins)
	{
		if (i >= value)
		{
			count++;
		}
		if (count == coins.size())
			return false;
	}

	// printf("general case:            ");
	// general case
	bool first_subset = false;
	for (int i = 0; i < coins.size(); i++)
	{
		//  bestSolution.push_back(coins[i]);
		if (UnlimitedCoinChange(coins, value - coins[i], coin_temp))
		{
			coin_temp.push_back(coins[i]);
			// cout << "The Value:" << value << "coin:" << coins[i] << endl;

			// printf("sublist: ");
			// cout << endl;
			// for (auto i : coin_temp)
			// {
			// 	cout << i << endl;
			// }
			if ((bestSolution.size() > coin_temp.size()))
			{
				bestSolution = coin_temp;
				coin_temp.clear();
				// return true;
			}

			if (bestSolution.empty() and first_subset == true and coin_temp.size() > 0)
			{
				bestSolution = coin_temp;
				coin_temp.clear();
				first_subset == false;
			}
			printf("sublist: ");
			cout << endl;
			for (auto i : coin_temp)
			{
				cout << i << endl;
			}
			// return true;
			//  if(coin_temp.size()==1){
			//      bestSolution = coin_temp;
			//      return true;
			//  }
			//  if(bestSolution.size()==1){
			//      return true;
			//  }
			// first_subset=true;
			first_subset = true;
		}
		// first_subset = true;
		//    printf("GGGGGGG");
	}
	// if ((bestSolution.size() > coin_temp.size()) and !coin_temp.empty())
	// {
	// 	bestSolution = coin_temp;
	// 	coin_temp.clear();
	// 	return true;
	// }

	// printf("done");
	// first_subset = true;
	printf("sublist: ");
	cout << endl;
	for (auto i : coin_temp)
	{
		cout << i << endl;
	}
	if ((bestSolution.size() < coin_temp.size()))
	{
		bestSolution = coin_temp;
		coin_temp.clear();
		// return true;
	}

	return true;
}

int main()
{
   vector<int> coins{2,5,3,10};
   vector<int> used;

   vector<int> values{4, 6,15, 18, 30, 41}; //use this to test
   
/*vector<vector<int>> results=subsets(coins,0,3);

for (int i = 0; i <results.size(); i++)
{
	cout << "Size: " << results[i].size();
	cout << " -> ";
	PrintVector(results[i]);
	cout << endl;
}*/


   //This part demo the CoinChange function: optimization problem
/*
   for (auto v: values) {
   //Todo: replace CoinChange with your CoinChangeUnlimited function... 
   	if (CoinChange (coins, 0, coins.size()-1, v, used))
   	{
		cout <<"value="<<v <<" True\n";
		//display used vector
        	for (int i=0;i<used.size();i++)
			cout <<used[i]<<" ";
        	cout<<endl;
   	}
   	else 
		cout <<"Value=" << v<<" False"<<endl;
   }*/


   //Test CoinChangeK
  cout <<"Enter coinchangek or unlimited to test the corresponding function:";
  string command;

  cin >> command;

  if (command=="coinchangek"){  
  	//we cannot make 20 using 2 or fewer coins
  	if (CoinChangeK (coins, 0, coins.size()-1, 20, 2)!=false || 
      		CoinChangeK (coins, 0, coins.size()-1, 5, 1)!=true)
  	{
		cout <<"fail coinchangek tests\n";
       		return 1; //faild coinchangeK test 
  	}
	else{
		cout <<"pass coinchangek tests\n";
		return 0; //pass coinchangeK test
	}
  } else if (command=="unlimited"){






   	//Test UnlimitedCoinChange 
	vector<int> bestSolution;

   	if (UnlimitedCoinChange (coins, 1,bestSolution)!=false) {
      		cout <<"Failed UnlimitedCoinChange case 1\n";
		return 1; //failed unlimited test 
	}

   	if (UnlimitedCoinChange (coins, 15, bestSolution)!=true) {
		cout <<"Failed UnlimitedCoinChange case 2\n";
		return 1;
	}
	vector<int> expectedSol{5,10}; 
        sort (bestSolution.begin(), bestSolution.end());
	if (bestSolution!=expectedSol){
		cout <<"Failed UnlimitedCoinChange case 2\n";
		return 1;

	}


   	if (UnlimitedCoinChange (coins, 30, bestSolution)!=true) {
		cout <<"Failed UnlimitedCoinChange case 3\n";
		return 1;
	}
	vector<int> expectedSol3{10,10,10}; 
        sort (bestSolution.begin(), bestSolution.end());
	if (bestSolution!=expectedSol3){
		cout <<"Failed UnlimitedCoinChange case 3\n";
		return 1;

	}

        cout <<"Pass unlimitedCoinChange cases\n";
        return 0;
  }

}

