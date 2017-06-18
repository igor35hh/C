def quicksort(arr):
	if len(arr)<2:
		return arr
	else:
		pivot = arr[0]
		less = [i for i in arr[1:] if i <= pivot]
		greater = [i for i in arr[1:] if i > pivot]
		return quicksort(less)+[pivot]+quicksort(greater)

arr = [8,6,19,11,1,2,3,5]
print(quicksort(arr))
