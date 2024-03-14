//10827157 吳添聖 & 10827133 鄧梓岑 
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <cstdlib> 
#include <fstream>  
#include <vector>
#include <string>
#include <string.h>
#include <queue>
#include <math.h>
#include <ctime> // clock 
#include <iomanip>

using namespace std ;

struct Data {
	int label ;
	string number ;
	string name ;
	string type ;
	string attack ;
	string defense ;
	
	string strhp ; // 用來轉換成int 
	int hp ;
	
	struct Data *L ;
	struct Data *R ;
};// 存取資料用的結構

vector <Data> list ;
vector <Data> list2 ;

int height ; // 紀錄最大樹高 

class Actions {
public:
	
	fstream olddata ;
	string temp, input ;
	
	bool Getact() {
	
		cin >> temp ; // input 檔案名稱
		input = "input" + temp + ".txt" ;

		olddata.open( input.c_str(), ios::in); // 讀出input檔 
		 
		if(!olddata) {
			if( temp == "0" ) return false ; // 結束程式 
			cout<< endl <<"### "<< input << " does not exist! Please try again! ###" ;
			cout << endl << "Input a file number [0: quit]: " ;
			return Getact() ; // 重新輸入至正確檔名 
		}
		
		else{   
			return true ;
		} // else 回傳true 
	} // end Getact() 打開檔案 

	void Save() {
		
		list.clear() ;
		
		struct Data *head = NULL ;
		height = 1 ; // 初始化height 
		
		char ch ; // 暫存input的字元 
		int tab = 0, templabel = -1 ; // 紀錄tab 
		bool in = false, first = true ;
		char tra[200] ; // 存檔案第一行 
		olddata.getline(tra, 200) ;
		
		while( !olddata.eof() ) {
			struct Data tempdata ;
			int heightch = 1 ;
			
			while( olddata.get(ch) && ch!='\n' ) {
				in = true ;
				
				if( tab == 0 && ch != '\t' ) {
					tempdata.number = tempdata.number + ch ;
				}
				else if( tab == 1 && ch != '\t' ) {
					tempdata.name = tempdata.name + ch ;
				}
				else if( tab == 2 && ch != '\t' ) {
					tempdata.type = tempdata.type + ch ;
				}
				else if( tab == 5 && ch != '\t' ) {
					tempdata.strhp = tempdata.strhp + ch ;
				}
				else if( tab == 6 && ch != '\t' ) {
					tempdata.attack = tempdata.attack + ch ;
				}
				else if( tab == 7 && ch != '\t' ) {
					tempdata.defense = tempdata.defense + ch ;
				}
				
				if( ch=='\t' ) tab++ ;
			}
			tempdata.hp = atoi( tempdata.strhp.c_str() ) ; // 把生命數值字串轉成數字
			templabel++ ;
			tempdata.label = templabel ;
			 
			if( head == NULL ) {
				head = new Data ;
				head->number = tempdata.number ;
				head->name = tempdata.name ;
				head->type = tempdata.type ;
				head->attack = tempdata.attack ;
				head->defense = tempdata.defense ;
				head->hp = tempdata.hp ;
				head->L = NULL, head->R = NULL ;
				list.push_back(tempdata) ;
			}
			else if( in==true && tab != 0 ) {
				list.push_back(tempdata) ;
				inserttree( tempdata, in, heightch, head ) ;
			}	
			
			if( heightch > height ) height = heightch ; // 更新heught  
			
			tab = 0 ; // 初始新一行的tab數量 
		}
	olddata.close() ;
	printout( list, false ) ;
	cout << "HP tree height = " << height << endl ;
	lookL( head ) ;
	lookR( head ) ;

	} // end save()
	
	void inserttree( struct Data tempdata, bool &in, int &heightch,  struct Data *head ) {
		bool finish = false ;
		Data *current = head; // 固定指向樹頂
		
		while( finish != true ) {
			if( tempdata.hp >= current->hp ) {
				if( current->R == NULL ) {
					current->R = new Data ;
					current = current->R ;
					current->label = tempdata.label ;
					current->number = tempdata.number ;
					current->name = tempdata.name ;
					current->type = tempdata.type ;
					current->attack = tempdata.attack ;
					current->defense = tempdata.defense ;
					current->hp = tempdata.hp ;
					current->L = NULL, current->R = NULL ;
					finish = true ; // 跳出迴圈 
				}
				else {
					current = current->R ;
				}
				heightch++ ;
			}
			else if( tempdata.hp < current->hp ) {
				if( current->L == NULL ) {
					current->L = new Data ;
					current = current->L ;
					current->label = tempdata.label ;
					current->number = tempdata.number ;
					current->name = tempdata.name ;
					current->type = tempdata.type ;
					current->attack = tempdata.attack ;
					current->defense = tempdata.defense ;
					current->hp = tempdata.hp ;
					current->L = NULL, current->R = NULL ;
					finish = true ; // 跳出迴圈 
				}
				else {
					current = current->L ; 
				}
				heightch++ ;
			}
			
		}
	} // end inserttree ;
	
	void printout( vector<Data>list, bool mission3 ) {
		
		cout << "\t" ;
		cout << "#" << "\t" ;
		cout << "Name" << "         \t\t\t" ;
		cout << "Type 1" << "     \t" ;
		cout << "HP" << "\t" ;
		cout << "Attack" << "\t" ;
		cout << "Defense" << "\t" << endl ;
		
		vector<Data>::iterator iter = list.begin() ;
		
		for(iter = list.begin(); iter != list.end(); ++iter) {
			if(mission3 == true){
				if( iter->label < 10 ) cout << "[ " << iter->label << "]\t" ;
				else cout << "[" << iter->label << "]\t" ;
			}
			else{
				if( iter->label < 9 ) cout << "[ " << iter->label+1 << "]\t" ;
				else cout << "[" << iter->label+1 << "]\t" ;
			}
			
			cout << iter->number << "\t" ;
			cout << iter->name << "   \t\t\t" ;
			cout << iter->type << "     \t" ;
			cout << iter->hp << "\t" ;
			cout << iter->attack << "\t" ;
			cout << iter->defense << "\t" << endl ;
		}
	}
	
	void lookL( struct Data *head ) {
		Data *current = head; // 固定指向樹頂
		
		while ( current->L != NULL ){
			current = current->L ;
		} // 找出最左邊的腳 
		
		cout << "Leftmost node:" << endl ;
		
		cout << "\t" ;
		cout << "#" << "\t" ;
		cout << "Name" << "         \t\t\t" ;
		cout << "Type 1" << "     \t" ;
		cout << "HP" << "\t" ;
		cout << "Attack" << "\t" ;
		cout << "Defense" << "\t" << endl ; // 提示語 
		
		if( current->label < 9 ) cout << "[ " << current->label+1 << "]\t" ;
		else cout << "[" << current->label+1 << "]\t" ;
		cout << current->number << "\t" ;
		cout << current->name << "   \t\t\t" ;
		cout << current->type << "     \t" ;
		cout << current->hp << "\t" ;
		cout << current->attack << "\t" ;
		cout << current->defense << "\t" << endl ;
	} // end lookL()
	
	void lookR( struct Data *head ) {
		Data *current = head; // 固定指向樹頂
		
		while ( current->R != NULL ){
			current = current->R ;
		} // 找出最左邊的腳 
		
		cout << "Rightmost node:" << endl ;
		
		cout << "\t" ;
		cout << "#" << "\t" ;
		cout << "Name" << "         \t\t\t" ;
		cout << "Type 1" << "     \t" ;
		cout << "HP" << "\t" ;
		cout << "Attack" << "\t" ;
		cout << "Defense" << "\t" << endl ; // 提示語 
		
		if( current->label < 9 ) cout << "[ " << current->label+1 << "]\t" ;
		else cout << "[" << current->label+1 << "]\t" ;
		cout << current->number << "\t" ;
		cout << current->name << "   \t\t\t" ;
		cout << current->type << "     \t" ;
		cout << current->hp << "\t" ;
		cout << current->attack << "\t" ;
		cout << current->defense << "\t" << endl ;
	} // end lookR()
	
	void build( int root ) {
		int child = 2 * root + 1 ;
		
		if( child < list.size() ) {
			int rightchild = child + 1 ;
			
			if( (rightchild < list.size()) && (list.at(rightchild).hp > list.at(child).hp) ) {
				child = rightchild ;
			}
			
			if( list.at(root).hp < list.at(child).hp) {
				int templabel = list.at(root).label ;
				list.at(root).label = list.at(child).label ;
				list.at(child).label = templabel ;
				
				Data temp = list.at(root) ;
				list.at(root) = list.at(child) ;
				list.at(child) = temp ;
				build( child ) ;
			}
		}
	}
	
	void callbuild() {
		
		int i = list.size()-1 ; 

		for( ; i>=0; i-- ) {
			build( i ) ;
		}
		
		int numlist = 1, height = 0 ; // numlist:list的資料數量， height算樹高 
		
		while ( numlist <= list.size() ) {
			numlist *= 2 ;
			height++ ;
		}
		
		int temp = pow( 2, height-1 ) -1 ; // 算最左邊最下面的index 
		
		list2.assign( list.begin(), list.end() ) ; // 供給mission3用 
		printout( list, false ) ;
		
		cout << endl << "HP heap geight= " << height << endl ;
		cout << "Leftmost node:" << endl ;
		
			cout << "\t" ;
			cout << "#" << "\t" ;
			cout << "Name" << "         \t\t\t" ;
			cout << "Type 1" << "     \t" ;
			cout << "HP" << "\t" ;
			cout << "Attack" << "\t" ;
			cout << "Defense" << "\t" << endl ; // 提示語 
		
			if( list.at( temp ).label < 9 ) cout << "[ " << list.at( temp ).label << "]\t" ;
			else cout << "[" << list.at( temp ).label << "]\t" ;
			cout << list.at( temp ).number << "\t" ;
			cout << list.at( temp ).name << "   \t\t\t" ;
			cout << list.at( temp ).type << "     \t" ;
			cout << list.at( temp ).hp << "\t" ;
			cout << list.at( temp ).attack << "\t" ;
			cout << list.at( temp ).defense << "\t" << endl ;
			
		cout << "Bottom:" << endl ;
		
			cout << "\t" ;
			cout << "#" << "\t" ;
			cout << "Name" << "         \t\t\t" ;
			cout << "Type 1" << "     \t" ;
			cout << "HP" << "\t" ;
			cout << "Attack" << "\t" ;
			cout << "Defense" << "\t" << endl ; // 提示語 
		
			if( list.back().label < 9 ) cout << "[ " << list.back().label << "]\t" ;
			else cout << "[" << list.back().label << "]\t" ;
			cout << list.back().number << "\t" ;
			cout << list.back().name << "   \t\t\t" ;
			cout << list.back().type << "     \t" ;
			cout << list.back().hp << "\t" ;
			cout << list.back().attack << "\t" ;
			cout << list.back().defense << "\t" << endl ;
	}
	
	bool deletetop() {
		if( list2.empty() ) return false ; // 要求回到mission2 
		else {
			cout << "The removed root:" << endl ;
				cout << "\t" ;
				cout << "#" << "\t" ;
				cout << "Name" << "         \t\t\t" ;
				cout << "Type 1" << "     \t" ;
				cout << "HP" << "\t" ;
				cout << "Attack" << "\t" ;
				cout << "Defense" << "\t" << endl ; // 提示語 
				
				cout << "     \t" ;
				cout << list2.at( 0 ).number << "\t" ;
				cout << list2.at( 0 ).name << "   \t\t\t" ;
				cout << list2.at( 0 ).type << "     \t" ;
				cout << list2.at( 0 ).hp << "\t" ;
				cout << list2.at( 0 ).attack << "\t" ;
				cout << list2.at( 0 ).defense << "\t" << endl << endl ;
			
			if( list2.size() > 1 ){
				list2.back().label = list2.at(0).label ;	
				list2.at(0) = list2.back() ;
				list2.erase( list2.end() ) ;
				callbuild3() ;
			}
			
			else{
				list2.erase( list2.end() ) ;
			}
			
			return true ;
		}
	}
	
	void build3( int root ) {
		int child = 2 * root + 1 ;
		
		if( child < list2.size() ) {
			int rightchild = child + 1 ;
			
			if( (rightchild < list2.size()) && (list2.at(rightchild).hp > list2.at(child).hp) ) {
				child = rightchild ;
			}
			
			if( list2.at(root).hp < list2.at(child).hp) {
				int templabel = list2.at(root).label ;
				list2.at(root).label = list2.at(child).label ;
				list2.at(child).label = templabel ;
				
				Data temp = list2.at(root) ;
				list2.at(root) = list2.at(child) ;
				list2.at(child) = temp ;
				build3( child ) ;
			}
		}
	}
	
	void callbuild3() {
		
		build3( 0 ) ;
		
		int numlist2 = 1, height = 0 ; // numlist2:list2的資料數量， height算樹高 
		
		while ( numlist2 <= list2.size() ) {
			numlist2 *= 2 ;
			height++ ;
		}
		
		int temp = pow( 2, height-1 ) -1 ; // 算最左邊最下面的index 
		
		printout( list2, true ) ;
		
		cout << endl << "HP heap geight= " << height << endl ;
		cout << "Leftmost node:" << endl ;
		
			cout << "\t" ;
			cout << "#" << "\t" ;
			cout << "Name" << "         \t\t\t" ;
			cout << "Type 1" << "     \t" ;
			cout << "HP" << "\t" ;
			cout << "Attack" << "\t" ;
			cout << "Defense" << "\t" << endl ; // 提示語 
		
			if( list2.at( temp ).label < 9 ) cout << "[ " << list2.at( temp ).label << "]\t" ;
			else cout << "[" << list2.at( temp ).label << "]\t" ;
			cout << list2.at( temp ).number << "\t" ;
			cout << list2.at( temp ).name << "   \t\t\t" ;
			cout << list2.at( temp ).type << "     \t" ;
			cout << list2.at( temp ).hp << "\t" ;
			cout << list2.at( temp ).attack << "\t" ;
			cout << list2.at( temp ).defense << "\t" << endl ;
			
		cout << "Bottom:" << endl ;
		
			cout << "\t" ;
			cout << "#" << "\t" ;
			cout << "Name" << "         \t\t\t" ;
			cout << "Type 1" << "     \t" ;
			cout << "HP" << "\t" ;
			cout << "Attack" << "\t" ;
			cout << "Defense" << "\t" << endl ; // 提示語 
		
			if( list2.back().label < 9 ) cout << "[ " << list2.back().label << "]\t" ;
			else cout << "[" << list2.back().label << "]\t" ;
			cout << list2.back().number << "\t" ;
			cout << list2.back().name << "   \t\t\t" ;
			cout << list2.back().type << "     \t" ;
			cout << list2.back().hp << "\t" ;
			cout << list2.back().attack << "\t" ;
			cout << list2.back().defense << "\t" << endl ;
	}
	
}; // end class action() 

int main(void) {
	 
	Actions action ;
	int command ;
	
	do {
		cout << endl << "****** Pokemon Tree and Heap ******" ;
	  	cout << endl << "* 0. QUIT                         *" ; 
	  	cout << endl << "* 1. Read a file to build BST     *" ;
	  	cout << endl << "* 2. Transform it into Max Heap   *" ;
	  	cout << endl << "***********************************" ;  	
		cout << endl << "Input a choice(0, 1, 2, 3): " ;
	  	cin >> command ; //輸入0or1or2or3指令 
  	
	  	switch(command){
	  		case 0 : break ; //跳出，結束 
	  		
	  		case 1 :
	  			cout << endl << "Input a file number [0: quit]: " ;
	  			if (!action.Getact()) break ;
  				else{
  					action.Save() ;
				}
	  			break ; // break from case1 
	  		
	  		case 2 : 
	  			if (list.empty()) {
	  				cout << "----- Execute Mission 1 first! -----" << endl ;
				}
	  			else {
	  				action.callbuild() ;
				}
				
	  			break ; // break from case2
	  			
	  		case 3 :  
				if (list.empty()) {
	  				cout << "----- Execute Mission 1 first! -----" << endl ;
				}
	  			else if(!action.deletetop()) cout << "----- Execute Mission 2 first! -----" << endl ; 
	  			
	  			break ; // break from case3
	  			
			default : cout << endl << "command does not exist !!" << endl ;
			break ;
		} // end switch
  	}while(command!=0); // break out the loop
  	
 	system ("pause") ; // 查看運作過程 
  	return 0 ;

} // end main() 
