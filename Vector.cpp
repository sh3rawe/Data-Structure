#include <bits/stdc++.h>

using namespace std;

class Vector
{
private:
    int *arr {nullptr};
    int Size {0};
    int capacity {0};

    void Expand_Capacity()
	{
	    capacity *= 2;
	    cout << "Expand Capacity to : " << capacity << endl;
	    int *arr2 = new int[capacity] { };
	    for(int i=0;i<Size;++i)
            arr2[i] = arr[i];

        swap(arr,arr2);
        delete[] arr2;
	}

public:
    Vector(int Size) : Size(Size)
    {
        if(Size < 0)
            Size = 1;
        capacity = Size+10;
        arr = new int[capacity] { };
    }
    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    int get_size(){
        return Size;
    }

    int get(int idx) {
		assert(0 <= idx && idx < Size);
		return arr[idx];
	}

	void set(int idx, int val) {
		assert(0 <= idx && idx < Size);
		arr[idx] = val;
	}

	void print()
	{
	    for(int i=0; i<Size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
	}

	int Find(int Value)
	{
	    for(int i=0;i<Size;++i)
        {
            if(arr[i] == Value)
                return i;
        }
        return -1;
	}

	int get_front(){
	    return arr[0];
	}

	int get_back(){
	    return arr[Size-1];
	}

	void Push_Back(int val)
	{
	    if(Size == capacity)
            Expand_Capacity();
        arr[Size++] = val;
	}

	void Insert(int idx , int value)
	{
	    assert(0 <= idx && idx<Size);

	    if(Size == capacity)
            Expand_Capacity();

        for(int i=Size-1; i>=idx; i--)
            arr[i+1] = arr[i];

        arr[idx] = value;
        ++Size;
	}

	void Right_Rotate()
	{
	    if(Size == capacity)
            Expand_Capacity();

        //store the first element in a temporary variable
        int temp = arr[0];
        //begin from end and shift data to right
        for(int i=Size-1;i>0;--i)
        {
            //without this condition the array
            //will print 4 4 1 2 3 , cuz position 1
            // in the array will copy from position 0
            //which is then will be 4
            if(i==1)
            {
                arr[i] = temp;
                break;
            }
            //putting the last element in the first position
            if(i == Size-1)
            {
                arr[0] = arr[Size-1];
            }
            //shifting the data to the right
            arr[i] = arr[i-1];
        }
	}

	void left_rotate()
	{
	    int temp = arr[0];
	    for(int i=0;i<Size-1;++i)
            arr[i] = arr[i+1];
        arr[Size-1] = temp;
	}

	void Right_Rotate(int times)
	{
	    // Every 'size' rotations, just return the array
        // to its original position
		// First, get rid of all of these multiple of size rotations
	    times%=Size;

	    while(times--)
        {
            Right_Rotate();
        }
	}

	int pop(int idx)
	{
	    assert(0<=idx && idx<Size);

	    int val = arr[idx];
	    // create an array of size-1
	    int *arr2 = new int[Size-1];
	    // then,shift all the data to the left
	    for(int i=idx;i<Size;++i)
            arr[i] = arr[i+1];
        // add the data to the new array
        for(int i=0;i<Size-1;++i)
            arr2[i] = arr[i];

        --Size;
        swap(arr,arr2);
        delete[] arr2;
        return val;
	}

	int find_transposition(int value)
	{
	    for(int i=0;i<Size;++i)
        {
            if(arr[i] == value)
            {
                if(i == 0)
                    return 0;
                swap(arr[i],arr[i-1]);
                return i-1;
            }
        }
        return -1;
	}
};

int main()
{
    int n = 5;
	Vector v(n);
	for (int i = 0; i < n; ++i)
		v.set(i, i);

	v.print();			// 0 1 2 3 4
	v.Right_Rotate(5 * 1000);
	v.print();			// 0 1 2 3 4
	v.Right_Rotate(2);
	v.print();			// 3 4 0 1 2
	v.left_rotate();
	v.print();			// 4 0 1 2 3

	int val = v.pop(2);
	cout << val << "\n";	// 1
	v.print();			// 4 0 2 3

	cout<<v.find_transposition(3)<<"\n";	// 2
	v.print();			// 4 0 3 2
    return 0;
}
