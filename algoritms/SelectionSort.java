package algoritms;

import java.util.Arrays;


public class SelectionSort {
	
	int TotalCount;
	int[] arr;
	
	public SelectionSort(int i) {
		arr = new int[i];
		TotalCount = 0;
	}

	public int findSmallest() {
        int smallest = arr[0];
        int smallestIndex = 0;
        for (int i = 0; i < TotalCount; i++) {
            if (arr[i] < smallest) {
                smallest = arr[i];
                smallestIndex = i;
            }
        }
        return smallestIndex;
    }
    
    public void reduce(int key) {
    	for(int k=key; k<TotalCount-1; k++) {
    		arr[k] = arr[k+1];
    	}
    	--TotalCount;
    }
    
    public void insert(int value) {
    	arr[TotalCount] = value;
    	TotalCount++;
    }
    
    public int[] selectionSort() {
        int[] newArr = new int[TotalCount];

        for (int i = 0; i < arr.length; i++) {
            int smallest = findSmallest();
            newArr[i] = arr[smallest];
            reduce(smallest);
        }

        return newArr;
    }

	public static void main(String[] args) {
		
		SelectionSort arr = new SelectionSort(5);
		arr.insert(5);
		arr.insert(3);
		arr.insert(6);
		arr.insert(2);
		arr.insert(10);
		
        System.out.println(Arrays.toString(arr.selectionSort()));
		
	}

}
