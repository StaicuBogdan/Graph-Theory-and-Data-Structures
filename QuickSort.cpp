#include <iostream>

using namespace std;

int partition(int v[100], int s, int e){
    int i=s;
    int pivot=v[e];
    for(int j=s;j<=e-1;j++){
        if(v[j]<pivot){
            swap(v[i],v[j]);
            i++;
        }
    }
    swap(v[i], v[e]);
    return i;
}

void quickSort(int v[100], int s, int e){
    if(s>=e)
        return;
    else{
        int p=partition(v,s,e);
        quickSort(v,s,p-1);
        quickSort(v,p+1,e);
    }
}

int main() {
    int v[100],n;
    cin>>n;
    for(int i=0;i<=n-1;i++)
        cin>>v[i];
    quickSort(v,0,n-1);
    for(int i=0;i<=n-1;i++)
        cout<<v[i]<<" ";
}
