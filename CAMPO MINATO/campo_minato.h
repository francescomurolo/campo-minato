#ifndef CAMPO_MINATO_H
#define CAMPO_MINATO_H

#include "boardgame.h"
#include <vector>
#include <string>

class Campo_minato : public BoardGame
{
    public:
        Campo_minato(int r, int c, int mine);
        void play_at(int x, int y);
        void flag_at(int x, int y);
        std::string get_val(int x, int y);
        bool finished();
        std::string message();
        int cols() { return row; }
        int rows() { return col; }
        bool get_losed() { return losed; }
	std::string get_nFlags();
    private:
        std::vector<std::vector<std::string>> matrice;
        std::vector<std::vector<int>> coordinate_mine;
        int row;
        int col;
        int n_mine;
	int n_flags;
        bool losed=false;
};

#endif // CAMPO_MINATO_H
