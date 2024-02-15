struct token {
    char val[50]; // Max length of 50
    int count; 
    int occupied;
};

void merge(struct token arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct token L[n1], R[n2];

    for(i = 0; i < n1; i++)
        L[i] = arr[l+i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m+1+j];

    i=0;
    j=0;

    k=l;
    while( i < n1 && j < n2 ) {
        if(L[i].count > R[j].count) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
}
void mergeSort(struct token arr[], int l, int r) {
    if(l<r) {
        int m = l + (r-l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }   
}