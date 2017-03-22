#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>

class SHIP{
    public : 

    int score ; 
    int id ; 
    long long int start ;
    long long int end ;

    SHIP(){
    }

    SHIP( int id, long long start , long long end ) : id(id) , start(start) , end(end) , score(0) {
    }
} ; 


bool startcmp( SHIP &a , SHIP &b ){
    if( a.start < b.start ) return true ; 
    else return false ; 
}

bool scorecmp( SHIP &a , SHIP &b ){
    if( a.score < b.score ) return true ; 
    else if( a.score > b.score ) return false ; 
    else if( a.id < b.id ) return true ;
    else return false ; 
}

void merge_and_update( std::vector<SHIP> &arr, int l, int r){
    if( l == r ) return ;
    else
    {
        int s = r-l+1 ; 
        // smaller array will be the left one
        merge_and_update( arr , l , l + s/2 - 1 ) ; 
        merge_and_update( arr, l + s/2 , r ) ; 
        // todo merge arrays with updating score
        int scoreadder = 0 ; 
        int l_ind = l , r_ind = l+s/2 , final = 0 ; 
        std::vector<SHIP> temp(s) ; 
        while( l_ind <= l + s/2 - 1 && r_ind <= r ){
            if( arr[l_ind].end > arr[r_ind].end ){ // copy right array element
                scoreadder++ ; 
                temp[final] = arr[r_ind] ; 
                r_ind++ ;
            }
            else{ // copy left array element
                arr[l_ind].score += scoreadder ; 
                temp[final] = arr[l_ind] ; 
                l_ind++ ; 
            }
            final++ ; 
        }
        while( l_ind <= l + s/2 - 1 ){  // copy remaining left array elements
            arr[l_ind].score += scoreadder ; 
            temp[final] = arr[l_ind] ; 
            l_ind++ ; 
            final++ ; 
        }
        while( r_ind <= r ) { // copy remaining right array elements
            temp[final] = arr[r_ind] ; 
            r_ind++ ;
            final++ ; 
        }
        std::copy( temp.begin() , temp.end() , arr.begin() + l ) ; 
        return ; 
    }
    
}

int main() {
    int n ; 
    std::ifstream f("./io/input002.txt") ; 
    f >> n ; 
    //std::cin >> n ; 
    std::vector<SHIP> arr(n) ; 
    for( int it = 0 ; it < n ; it++ ){
        int i ; 
        long long int s,e ; 
        //std::cin >> i >> s >> e ;
        f >> i >> s >> e ;
        arr[it] = SHIP(i,s,e) ; 
    }
    sort(arr.begin(), arr.end(), startcmp) ;
    merge_and_update( arr , 0, arr.size()-1 ) ;
    sort(arr.begin(), arr.end(), scorecmp ) ; 
    for( auto it = arr.begin() ; it != arr.end() ; it++ ){
        std::cout << it->id << ' ' << it->score << '\n' ; 
    }
}