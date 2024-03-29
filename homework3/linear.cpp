

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	if (n < 1)
	{
		return true;
	}
	else if (n == 1)
	{
		return somePredicate(a[0]); //test a[0]
	}
	else if (somePredicate(a[n-1]))
	{
		allTrue(a, n-1); //examine a[0] to a[n-2]
	}
	else
	{
		return false;
	}
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n < 1)
	{
		return 0;
	}
	else if (n == 1)
	{
		if (!somePredicate(a[0])) //if a[0] is false
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (!somePredicate(a[n - 1])) //if a[n-1] is false
	{
		return (countFalse(a, n - 1) + 1); //increase the count
	}
	else
	{
		return (countFalse(a, n - 1)); //not increase the count
	}
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n < 1)
	{
		return -1;
	}
	else
	{
		if (!somePredicate(a[n - 1]) && firstFalse(a, n - 1) == -1) //a[n-1] is false and no one false ahead
		{
			return n - 1;
		}
		else
		{
			return firstFalse(a, n - 1); //go ahead to find firstfalse
		}
	}

}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}
	else if (n == 1)
	{
		return 0;
	}
	else if (a[n-1] < a[indexOfLeast(a, n - 1)]) //if a[n-1] is smaller
	{
		return n-1;
	}
	else
	{
		return indexOfLeast(a, n - 1); 
	}
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 == 0)
	return true;
	else if (n1 >= n2) //is possible to include
	{
		if ((a1[n1 - 1] == a2[n2 - 1]))//the same string
		{
			return includes(a1, n1 - 1, a2, n2 - 1); //test the next one
		}
		else
		{
			return includes(a1, n1 - 1, a2, n2); //go to the next one to find
		}
	}
	else
	{
		return false;
	}
}


