//print with an array
void printQarr(const, Queue *1) {
	long length
	void **array = q->toArray(1, &length);
	int i;
	for (i=0, i<length; i++) {
		printf("%s\n", (char*)array[i]);
	}
	free(array)
}

//print with an iterator instead of an array
void printQit(const Queue *q) {
	const Iterator *it = NULL;
	it = q->itCreate(q);
	while (it->hasNext(it)) {
		char v;
		it->next(it, ADT_ADDRESS(&v));
		printf("%c", v);
	}
	it->destroy(it);
}