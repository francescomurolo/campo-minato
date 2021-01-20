#include "campo_minato.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Campo_minato::Campo_minato(int h, int w, int m)
{
    row=h;
    col=w;
    n_mine=m;
    n_flags=m;
    matrice.assign(row,std::vector<string>(col," "));
    std::srand(std::time(nullptr));

    for(int i=0;i<n_mine;++i){
		int rand_r= std::rand()%h;
		int rand_c= std::rand()%w;
        bool trovato=false;

		for(unsigned c=0;c<coordinate_mine.size();++c){
            if(rand_r==coordinate_mine[c][0] && rand_c==coordinate_mine[c][1]){
                trovato=true;
                i--;
            }
		}

		if(trovato==false){
            std::vector<int> coordinate = {rand_r,rand_c};
            coordinate_mine.push_back(coordinate);
		}
	}
}

void Campo_minato::play_at(int x, int y){
    if(matrice[x][y]==" "){
        bool trovato=false;

        for(int i=0;i<n_mine && trovato==false;++i){
            if(coordinate_mine[i][0]==x && coordinate_mine[i][1]==y){
                trovato=true;
            }
        }

        if(trovato){
            matrice[x][y]="M";
            losed=true;
        }else{
            int count=0;
            for(int i=0;i<n_mine && trovato==false;++i){
                if(x>0 && y>0 && coordinate_mine[i][0]==x-1 && coordinate_mine[i][1]==y-1){
                    count++;
                }
                if(x>0 && coordinate_mine[i][0]==x-1 && coordinate_mine[i][1]==y){
                    count++;
                }
                if(x>0 && y<(col-1) && coordinate_mine[i][0]==x-1 && coordinate_mine[i][1]==y+1){
                    count++;
                }
                if(y<(col-1) && coordinate_mine[i][0]==x && coordinate_mine[i][1]==y+1){
                    count++;
                }
                if(x<(row-1) && y<(col-1) && coordinate_mine[i][0]==x+1 && coordinate_mine[i][1]==y+1){
                    count++;
                }
                if(x<(row-1) && coordinate_mine[i][0]==x+1 && coordinate_mine[i][1]==y){
                    count++;
                }
                if(x<(row-1) && y>0 && coordinate_mine[i][0]==x+1 && coordinate_mine[i][1]==y-1){
                    count++;
                }
                if(y>0 && coordinate_mine[i][0]==x && coordinate_mine[i][1]==y-1){
                    count++;
                }
            }
            matrice[x][y]=std::to_string(count);
            if(count==0 && trovato==false){
                if(x>0 && y>0)
                    this->play_at(x-1,y-1);
                if(x>0)
                    this->play_at(x-1,y);
                if(x>0 && y<col-1)
                    this->play_at(x-1,y+1);
                if(y<col-1)
                    this->play_at(x,y+1);
                if(x<row-1 && y<col-1)
                    this->play_at(x+1,y+1);
                if(x<row-1)
                    this->play_at(x+1,y);
                if(x<row-1 && y>0)
                    this->play_at(x+1,y-1);
                if(y>0)
                    this->play_at(x,y-1);
            }
        }
    }
}

void Campo_minato::flag_at(int x, int y){
    if(matrice[x][y]==" "){
	matrice[x][y]="B";
	n_flags--;
    }else if(matrice[x][y]=="B"){
	matrice[x][y]=" ";
	n_flags++;
    }else{
	int count=0;
        if(x>0 && y>0)
	    if(matrice[x-1][y-1]=="B")
		count++;
	if(x>0)
	    if(matrice[x-1][y]=="B")
		count++;
	if(x>0 && y<col-1)
	    if(matrice[x-1][y+1]=="B")
		count++;
	if(y<col-1)
	    if(matrice[x][y+1]=="B")
		count++;
	if(x<row-1 && y<col-1)
	    if(matrice[x+1][y+1]=="B")
		count++;
	if(x<row-1)
	    if(matrice[x+1][y]=="B")
		count++;
	if(x<row-1 && y>0)
	    if(matrice[x+1][y-1]=="B")
		count++;
	if(y>0)
	    if(matrice[x][y-1]=="B")
		count++;

	if(matrice[x][y]==std::to_string(count)){
		if(x>0 && y>0)
		    if(matrice[x-1][y-1]==" ")
			this->play_at(x-1,y-1);
		if(x>0)
		    if(matrice[x-1][y]==" ")
			this->play_at(x-1,y);
		if(x>0 && y<col-1)
		    if(matrice[x-1][y+1]==" ")
			this->play_at(x-1,y+1);
		if(y<col-1)
		    if(matrice[x][y+1]==" ")
			this->play_at(x,y+1);
		if(x<row-1 && y<col-1)
		    if(matrice[x+1][y+1]==" ")
			this->play_at(x+1,y+1);
		if(x<row-1)
		    if(matrice[x+1][y]==" ")
			this->play_at(x+1,y);
		if(x<row-1 && y>0)
		    if(matrice[x+1][y-1]==" ")
			this->play_at(x+1,y-1);
		if(y>0)
		    if(matrice[x][y-1]==" ")
			this->play_at(x,y-1);
	}else{
		int count2=0;
		if(x>0 && y>0)
		    if(matrice[x-1][y-1]==" " || matrice[x-1][y-1]=="B")
			count2++;
		if(x>0)
		    if(matrice[x-1][y]==" " || matrice[x-1][y]=="B")
			count2++;
		if(x>0 && y<col-1)
		    if(matrice[x-1][y+1]==" " || matrice[x-1][y+1]=="B")
			count2++;
		if(y<col-1)
		    if(matrice[x][y+1]==" " || matrice[x][y+1]=="B")
			count2++;
		if(x<row-1 && y<col-1)
		    if(matrice[x+1][y+1]==" " || matrice[x+1][y+1]=="B")
			count2++;
		if(x<row-1)
		    if(matrice[x+1][y]==" " || matrice[x+1][y]=="B")
			count2++;
		if(x<row-1 && y>0)
		    if(matrice[x+1][y-1]==" " || matrice[x+1][y-1]=="B")
			count2++;
		if(y>0)
		    if(matrice[x][y-1]==" " || matrice[x][y-1]=="B")
			count2++;

		if(matrice[x][y]==std::to_string(count2)){
			if(x>0 && y>0)
			    if(matrice[x-1][y-1]==" ")
				this->flag_at(x-1,y-1);
			if(x>0)
			    if(matrice[x-1][y]==" ")
				this->flag_at(x-1,y);
			if(x>0 && y<col-1)
			    if(matrice[x-1][y+1]==" ")
				this->flag_at(x-1,y+1);
			if(y<col-1)
			    if(matrice[x][y+1]==" ")
				this->flag_at(x,y+1);
			if(x<row-1 && y<col-1)
			    if(matrice[x+1][y+1]==" ")
				this->flag_at(x+1,y+1);
			if(x<row-1)
			    if(matrice[x+1][y]==" ")
				this->flag_at(x+1,y);
			if(x<row-1 && y>0)
			    if(matrice[x+1][y-1]==" ")
				this->flag_at(x+1,y-1);
			if(y>0)
			    if(matrice[x][y-1]==" ")
				this->flag_at(x,y-1);
   		}
	}
    }

}

string Campo_minato::get_val(int x, int y){
    return matrice[x][y];
}

bool Campo_minato::finished(){
    bool ctrl=false;

    for(int i=0;i<n_mine && ctrl==false;++i){
        for(int r=0;r<row && ctrl==false;r++){
            for(int c=0;c<col && ctrl==false;c++)
                if((coordinate_mine[i][0]==r && coordinate_mine[i][1]==c) && matrice[r][c]=="M")
                    ctrl=true;
        }
    }

    if(ctrl==false){
	bool ctrl_2=true;
        for(int r=0;r<row && ctrl_2==true;r++){
            for(int c=0;c<col && ctrl_2==true;c++)
                if(matrice[r][c]==" ")
                    ctrl_2=false;	
        }
        return ctrl_2;
    }

    return ctrl;
}

std::string Campo_minato::message(){
    if(losed==false)
        return "Hai vinto!";
    return "Hai perso!";
}

std::string Campo_minato::get_nFlags(){
    return std::to_string(n_flags);
}
