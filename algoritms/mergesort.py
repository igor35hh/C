def merge(left, right):
	lst = []
	while left and right:
		if left[0] < right[0]:
			lst.append(left.pop(0))
		else:
			lst.append(right.pop(0))
	if left:
		lst.extend(left)
	if right:
		lst.extend(right)
	return lst

def mergesort(lst):
	lenght = len(lst)
	if lenght >= 2:
		mid = int(lenght/2)
		lst = merge(mergesort(lst[:mid]), mergesort(lst[mid:]))
	return lst

l = list("12348723400023498234")
print(mergesort(l))
