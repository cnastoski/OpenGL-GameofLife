if (i % 20 == 0) {
    neighbors[0] = i - 1;
    neighbors[3] = i + 19;
    neighbors[5] = i + 39;
}
if (i % 20 == 9) {
    neighbors[2] = i - 39;
    neighbors[4] = i - 19;
    neighbors[7] = i + 1;
}









if (i % 20 == 0) {
    neighbors.erase(neighbors.begin());
    neighbors.erase(neighbors.begin() + 3);
    neighbors.erase(neighbors.begin() + 5);
}
if (i % 20 == 9) {
    neighbors.erase(neighbors.begin() + 2);
    neighbors.erase(neighbors.begin() + 4);
    neighbors.pop_back();



    for (float posy = 499.5; posy >= -499.5; posy -= 1) {
        for (float posx = -499.5; posx <= 499.5; posx += 1) {
            Cell tempcell = { posx, posy, false };
            cellarray.push_back(tempcell);
            nextgenarray.push_back(tempcell);
        }
    }
}









for (float posy = 247.5; posy >= -247.5; posy -= 5) {
    for (float posx = -247.5; posx <= 247.5; posx += 5) {
        //randomize colors
        std::vector<int> random_cols{ 0,0,0 };
        for (int c = 0; c <= 2; c++) {
            if (rand() % 100 < color_prob) {
                random_cols[c] = 255;
            }
            else {
                random_cols[c] = 0;
            }
        }
        if (random_cols[0] == 0 && random_cols[1] == 0 && random_cols[2] == 0) {
            random_cols[rand() % 3] = 255;
        }

        Cell tempcell = { posx, posy, false, random_cols };

        cellarray.push_back(tempcell);
        nextgenarray.push_back(tempcell);
    }
}



cellarray[400].alive = true;
cellarray[850].alive = true;

//cellarray[400].colors = {43,34,255};
//cellarray[850].colors = {255,0,0};
//cellarray[211].alive = true;
//cellarray[192].alive = true;
//cellarray[213].alive = true;
//cellarray[234].alive = true;
srand(seed);
for (int i = 0; i <= 9999; i++) {
    if (rand() % 100 < 20) {
        cellarray[i].alive = true;
    }
}
