#include "Plotter.h"
#include <iostream>
#include <strlib.h>
using namespace std;

void runPlotterScript(istream& input) {
    //initalize the plotter
    double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    PenStyle style = {1, "black"};
    bool pen_down = false; //default state is penUp

    //read the "input" file
    for (string line; getline(input, line);) {
        string low_line = toLowerCase(line);
        string del = " ";
        Vector<string> words = stringSplit(low_line, del);

        //update x1, y1
        if (words.size() == 3) {
            x1 = stringToReal(words[1]);
            y1 = stringToReal(words[2]);
        }

        //update style width or color
        if (startsWith(low_line, "penwidth")) {
            style.width = stringToReal(words[1]);
        }
        else if (startsWith(low_line, "pencolor")) {
            style.color = words[1];
        }

        //update pen_down to true/false
        else if (startsWith(low_line, "penup")) {
            pen_down = false;
        }

        else if (startsWith(low_line, "pendown")) {
            pen_down = true;
        }

        //plot using drawLine() if pen_down is true
        if (pen_down == true) {
            if (startsWith(low_line, "moveabs")) {
                drawLine(x0,y0,
                         x1, y1,
                         style);
            }
            else if (startsWith(low_line, "moverel")) {

                drawLine(x0, y0,
                         x0 + x1, y0 + y1,
                         style);
            }
        }
        //update x0, y0 depending on relative/absolute move made
        if (words[0] == "moverel") {
            x0 += x1;
            y0 += y1;
        }
        else if (words[0] == "moveabs") {
            x0 = x1;
            y0 = y1;
        }
    }
}
