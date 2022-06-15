#include <string>
#include <fstream>
#include <iostream>
#include <array>
/* #include "../includes/road.h" */
/* #include "../includes/car.h" */
#include "../includes/common.h"
#include <vector>
#include <map>

typedef std::array<int, 2> intCoord;
typedef std::array<float, 2> floatCoord;

class Map {
    public:
        int width;
        int height;
        std::vector<Road> roads;
        std::vector<Car> cars;
        std::map<intCoord, int> roadSourceMap;  // Map of source coords to road uniqueID
        // Each road is uniquely defined by it's source coordinates because
        // for our model, two roads cannot have the same source coordinates.
        Map(int mapWidth, int mapHeight, 
                std::vector<Road> mapRoads) {
            width = mapWidth;
            height = mapHeight;
            roads = mapRoads;  // Coordtor containing all road objects for the map
            for (Road r: roads) {
                roadSourceMap[r.source] = r.uniqueID;
            }
        }

        // Convert a std::array<int, 2> {i, j} to a string of the form "[i, j]"
        std::string _arrToPyListString(intCoord intArr) {
            std::string pyListString = '[' + std::to_string(intArr[0]) + ',' + 
                std::to_string(intArr[1]) + ']';
            return pyListString;
        }

        std::string _arrToPyListString(floatCoord floatArr) {
            std::string pyListString = '[' + std::to_string(floatArr[0]) + ',' + 
                std::to_string(floatArr[1]) + ']';
            return pyListString;
        }

        // Write the map data to a csv file with given fileName
        void writeRoadsToCSV(std::string fileName) {
            std::ofstream mapFile(fileName);
            // Road class attributes for column names
            mapFile << "uniqueID;flowDir;topLeft;bottomRight\n";
            for(Road r : roads) {
                mapFile << r.uniqueID << ';' << _arrToPyListString(r.flowDir) <<
                    ';' << _arrToPyListString(r.topLeft) << ';' <<
                    _arrToPyListString(r.bottomRight) << '\n';
            }
            std::cout << "Successfully wrote map to " << fileName << std::endl;
            mapFile.close();
        }
        // Write the map data to a python file with given fileName
        /* void writeMaptoPyFile(std::string fileName) { */
        /*     std::ofstream mapFile(fileName); */
        /*     mapFile << "map_width = " << width << '\n'; */
        /*     mapFile << "map_height = " << height << '\n'; */
        /*     mapFile << "road_number = " << roads.size() << '\n'; */
        /*     for (Road r : roads) { */
        /*         mapFile << "# ---------------------------------------------\n"; */
        /*         mapFile << "length" << r.uniqueID << " = " << r.length << '\n'; */
        /*         mapFile << "orient" << r.uniqueID << " = " << '"' << r.orient << */
        /*             '"'<< '\n'; */
        /*         mapFile << "source" << r.uniqueID << " = " << */
        /*             '[' << r.source[0] << ", " << r.source[1] << ']' << '\n'; */
        /*         mapFile << "sink" << r.uniqueID << " = " << */
        /*             '[' << r.sink[0] << ", " << r.source[1] << ']' << '\n'; */
        /*         mapFile << "flow_dir" << r.uniqueID << " = " << '"' << */
        /*             r.flowDir << '"'<< '\n'; */
        /*         mapFile << "top_left" << r.uniqueID << " = " << */
        /*             '[' << r.topLeft[0] << ", " << r.topLeft[1] << ']' << '\n'; */
        /*         mapFile << "bottom_right" << r.uniqueID << " = " << */
        /*             '[' << r.bottomRight[0] << ", " << r.bottomRight[1] << */
        /*             ']' << '\n'; */
        /*     } */
        /*     std::cout << "Successfully wrote roads to " << fileName << std::endl; */
        /*     mapFile.close(); */
        /* } */
        void writeCarsToCSV(std::string fileName) {
            std::ofstream carFile(fileName);
            for (int i = 0; i < totalFrameNum; i++) {
                for (Car c : cars) {
                    carFile << c.carPos[i][0] << ',' << c.carPos[i][1] <<
                        ',' << c.carDir[i][0] << ',' << c.carDir[i][1] << ';';
                }
                carFile << '\n';
            }
            std::cout << "Successfully wrote cars to " << fileName << std::endl;
            carFile.close();
        }

};
