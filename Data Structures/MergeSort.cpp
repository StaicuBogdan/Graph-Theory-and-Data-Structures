#include <iostream>

using namespace std;

void interclasare(int x[100], int y[100], int v[100], int s, int e){
    int m=(s+e)/2;
    int i=s;
    int j=m+1;
    int k=s;
    while(i<=m && j<=e){
        if(x[i]<y[j]){
            v[k]=x[i];
            i++;
            k++;
        }
        else{
            v[k]=y[j];
            j++;
            k++;
        }
    }
    while(i<=m){
        v[k]=x[i];
        i++;
        k++;
    }
    while(j<=e){
        v[k]=y[j];
        j++;
        k++;
    }
}

void mergeSort(int v[100],int s, int e){
    if(s>=e)
        return;
    int m=(s+e)/2;
    int x[100],y[100];
    for(int i=0;i<=m;i++)
        x[i]=v[i];
    for(int i=m+1;i<=e;i++)
        y[i]=v[i];
    mergeSort(x,s,m);
    mergeSort(y,m+1,e);
    interclasare(x, y, v, s, e);
}

int main() {
    int v[100],n;
    cin>>n;
    for(int i=0;i<=n-1;i++)
        cin>>v[i];
    mergeSort(v,0,n-1);
    for(int i=0;i<=n-1;i++)
        cout<<v[i]<<" ";
}
