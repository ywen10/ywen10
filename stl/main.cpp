#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
class Shape {
public:
    double x,y,z;
    Shape(double x,double y, double z):x(x),y(y),z(z){}
    virtual ~Shape(){}
    virtual void save(string name)=0;
};

class Point{
public:
    double x,y,z;
    Point(double x,double y, double z):x(x),y(y),z(z){}
    ~Point(){}
    friend Point get_Normal(Point p1,Point p2,Point p3)

    {
        double a = ( (p2.y-p1.y)*(p3.z-p1.z)-(p2.z-p1.z)*(p3.y-p1.y) );
        double b = ( (p2.z-p1.z)*(p3.x-p1.x)-(p2.x-p1.x)*(p3.z-p1.z) );
        double c = ( (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x) );
        return Point(a,b,c);
    }
};

class Cylinder : public Shape{
private:
	double r, h;
	int facets;
    vector<Point *> Points;
    vector<Point *> normals;
public:
	Cylinder(double x, double y, double z, double r, double h, int facets):Shape(x, y, z),r(r),h(h),facets(facets) {

    }
    void save(string name){
        ofstream file;
        file.open(name,ios_base::app);
        file<<x<<y<<z;
    }

};

class Cube: public Shape {
private:
	double size;
    vector<Point> points;
    vector<Point> normals;
public:
	Cube(double x, double y, double z, double size) : Shape(x, y, z),size(size) {

            Point p0(x+size/2,y+size/2,z+size/2);
            Point p1(x+size/2,y-size/2,z+size/2);
            Point p2(x+size/2,y-size/2,z-size/2);
            Point p3(x+size/2,y+size/2,z-size/2);

        Point p4(x+size/2,y-size/2,z+size/2);
        Point p5(x-size/2,y-size/2,z+size/2);
        Point p6(x-size/2,y-size/2,z-size/2);
        Point p7(x+size/2,y-size/2,z-size/2);

        Point p8(x-size/2,y-size/2,z+size/2);
        Point p9(x-size/2,y+size/2,z+size/2);
        Point p10(x-size/2,y+size/2,z-size/2);
        Point p11(x-size/2,y-size/2,z-size/2);

        Point p12(x-size/2,y+size/2,z+size/2);
        Point p13(x+size/2,y+size/2,z+size/2);
        Point p14(x+size/2,y+size/2,z-size/2);
        Point p15(x-size/2,y+size/2,z-size/2);

        Point p16(x-size/2,y+size/2,z+size/2);
        Point p17(x-size/2,y-size/2,z+size/2);
        Point p18(x+size/2,y-size/2,z+size/2);
        Point p19(x+size/2,y+size/2,z+size/2);

        Point p20(x-size/2,y+size/2,z-size/2);
        Point p21(x+size/2,y+size/2,z-size/2);
        Point p22(x+size/2,y-size/2,z-size/2);
        Point p23(x-size/2,y-size/2,z-size/2);

        points.push_back(p0);
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        points.push_back(p4);
        points.push_back(p5);
        points.push_back(p6);
        points.push_back(p7);
        points.push_back(p8);
        points.push_back(p9);
        points.push_back(p10);
        points.push_back(p11);
        points.push_back(p12);
        points.push_back(p13);
        points.push_back(p14);
        points.push_back(p15);
        points.push_back(p16);
        points.push_back(p17);
        points.push_back(p18);
        points.push_back(p19);
        points.push_back(p20);
        points.push_back(p21);
        points.push_back(p22);
        points.push_back(p23);
        normals.push_back(Point(1,0,0));
        normals.push_back(Point(0,-1,0));
        normals.push_back(Point(-1,0,0));
        normals.push_back(Point(0,1,0));
        normals.push_back(Point(0,0,1));
        normals.push_back(Point(0,0,-1));


    }
    void save(string name){
        ofstream file;
        file.open(name,ios_base::app);
        file<<"solid OpenSCAD_Cube"<<endl;
        for (int i = 0; i <6 ; ++i) {
            file<<"facet normal"<<" "<<normals[i].x<<" "<<normals[i].y<<" "<<normals[i].z<<endl;
            file<<"outer loop"<<endl;
            file<<"vertex"<<" "<<points[4*i].x<<" "<<points[4*i].y<<" "<<points[4*i].z<<endl;
            file<<"vertex"<<" "<<points[4*i+1].x<<" "<<points[4*i+1].y<<" "<<points[4*i+1].z<<endl;
            file<<"vertex"<<" "<<points[4*i+2].x<<" "<<points[4*i+2].y<<" "<<points[4*i+2].z<<endl;
            file<<"endloop"<<endl;
            file<<"endfacet"<<endl;
            file<<"facet normal"<<" "<<normals[i].x<<" "<<normals[i].y<<" "<<normals[i].z<<endl;
            file<<"outer loop"<<endl;
            file<<"vertex"<<" "<<points[4*i+2].x<<" "<<points[4*i+2].y<<" "<<points[4*i+2].z<<endl;
            file<<"vertex"<<" "<<points[4*i+3].x<<" "<<points[4*i+3].y<<" "<<points[4*i+3].z<<endl;
            file<<"vertex"<<" "<<points[4*i].x<<" "<<points[4*i].y<<" "<<points[4*i].z<<endl;
            file<<"endloop"<<endl;
            file<<"endfacet"<<endl;
        }

        file<<"endsolid OpenSCAD_Cube"<<endl;
    }



};

class CAD {
private:
    vector<Shape *> shapes;
public:

    void add(Shape *a) {
        shapes.push_back(a);
    }

    void write(string name) {
        ofstream file(name);
        for (auto s : shapes) {
            s->save(name);
        }
    }
};



int main() {
    CAD c;
    c.add(new Cube(0, 0, 0, 5));
    c.add(new Cylinder(100, 0, 0, 3, 10, 10));
    c.write("test.stl");
}
