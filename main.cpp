#include <stdio.h>
#include <armadillo>
#include <vector>
#include "v3.h"
#include "RoomObject.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Phong.h"
#include "Room.h"
using namespace arma;

/* Method Declarations */
int unit_tests();

int main(int argc, char **argv)
{
    unit_tests();
    return 0;
}

int unit_tests(){
    Phong p = Phong( v3(0,.2, 0), v3(0, .5, 0), v3(1, 1, 1) , 1);
    
//    //try a regular mesh initialization
//    Mesh m1 = Mesh( v3(0,0,0) , p );
//    v3 triangle_vertices[] ={v3(1,1,0),
//                             v3(0,0,0),
//                             v3(0,1,0)};
//    m1.add_triangle( Triangle(triangle_vertices) );
//    
//    //initialize it with a sphere
//    std::vector<Triangle> triangles = Mesh::generate_unit_sphere(32, 16);
//    Mesh m2 = Mesh( v3(0,0,0) , p, triangles);
//    
//    //transform my matrices
      mat t_mat = RoomObject::uniform_scale_transform(2);
//    
//    m1.transform(&t_mat);
//    m2.transform(&t_mat);
//    
//    //Let's see what we got
//    std::cout << m1.to_str();
//    
//    std::cout << "----" << std::endl;
    
    //std::cout << m2.to_str();
    
    //Create a camera
    mat44 camera = mat44 {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
    //Create a room maybe?
    Mesh m3 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    m3.transform(&t_mat);
    mat44 translation_mat = RoomObject::translate_transform( v3(0,0,-7) );
    m3.transform(&translation_mat);
    
    Mesh m4 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    //m3.transform(&t_mat);
    translation_mat = RoomObject::translate_transform( v3(0,0,-9) );
    m4.transform(&translation_mat);
    
    
    Room room = Room(camera, -.1, .1, -.1, .1, -.1, -1000, v3(0,0,0));
    
    room.addObject(&m3);
    room.addObject(&m4);
    
    Renderer renderer = Renderer(512, 512, 1);
    
    room.draw(&renderer);
    
    renderer.render_ppm("./Images/out.ppm");
    
    return 0;
}
