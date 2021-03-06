#include <gtest/gtest.h>
#include <iostream>
#include <ctime>
#include <ogr_geometry.h>
#include <arrow/api.h>
#include <arrow/array.h>

#include "arrow/gis_api.h"
#include "utils/check_status.h"

using namespace zilliz::gis;
#define common_test_cases \
  auto p1 = "POINT (0 1)";\
\
  auto p2 = "LINESTRING (0 0, 0 1)";\
  auto p3 = "LINESTRING (0 0, 1 0)";\
  auto p4 = "LINESTRING (0 0, 1 1)";\
  auto p5 = "LINESTRING (0 0, 0 1, 1 1)";\
  auto p6 = "LINESTRING (0 0, 1 0, 1 1)";\
  auto p7 = "LINESTRING (0 0, 1 0, 1 1, 0 0)";\
  \
  auto p8 = "POLYGON ((0 0, 1 0, 1 1, 0 1, 0 0))";\
  auto p9 = "POLYGON ((0 0, 0 1, 1 1, 1 0, 0 0))";\
  auto p10 = "POLYGON ((0 0, 1 0, 1 1, 0 0))";\
  auto p11 = "POLYGON ((0 0, 0 1, 1 1, 0 0))";\
  \
  auto p12 = "MULTIPOINT (0 0, 1 0, 1 2)";\
  auto p13 = "MULTIPOINT (0 0, 1 0, 1 2, 1 2)";\
  \
  auto p14 = "MULTILINESTRING ( (0 0, 1 2), (0 0, 1 0, 1 1) )";\
  auto p15 = "MULTILINESTRING ( (0 0, 1 2), (0 0, 1 0, 1 1) )";\
  auto p16 = "MULTILINESTRING ( (0 0, 1 2), (0 0, 1 0, 1 1),(-1 2,3 4,9 -3,-4 100) )";\
  \
  auto p17 = "MULTIPOLYGON ( ((0 0, 1 0, 1 1,0 0)) )";\
  auto p18 = "MULTIPOLYGON ( ((0 0, 1 1, 1 0,0 0)) )";\
  \
  auto p19 = "MULTIPOLYGON ( ((0 0, 0 4, 4 4, 4 0, 0 0)), ((0 0, 4 0, 4 1, 0 1, 0 0)) )";\
  auto p20 = "MULTIPOLYGON ( ((0 0, 4 0, 4 1, 0 1, 0 0)), ((0 0, 0 4, 4 4, 4 0, 0 0)) )";\
  auto p21 = "MULTIPOLYGON ( ((0 0, 1 0, 1 1, 0 1, 0 0)), ((0 0, 0 4, 4 4, 4 0, 0 0)) )";\
  auto p22 = "MULTIPOLYGON ( ((0 0, 4 0, 4 4, 0 4, 0 0)), ((0 0, 0 1, 4 1, 4 0, 0 0)) )";\
  auto p23 = "MULTIPOLYGON ( ((0 0, 0 1, 4 1, 4 0, 0 0)), ((0 0, 4 0, 4 4, 0 4, 0 0)) )";\
  auto p24 = "MULTIPOLYGON ( ((0 0, 0 1, 1 1, 1 0, 0 0)), ((0 0, 4 0, 4 4, 0 4, 0 0)) )";\
  \
  auto p25 = "MULTIPOLYGON ( ((0 0, 4 0, 4 4, 0 4, 0 0)), ((0 0, 1 0, 1 1, 0 1, 0 0)) )";\
  auto p26 = "MULTIPOLYGON ( ((0 0, 1 0, 1 1, 0 1, 0 0)), ((0 0, 4 0, 4 4, 0 4, 0 0)) )";\
  auto p27 = "MULTIPOLYGON ( ((0 0, 0 4, 4 4, 4 0, 0 0)), ((0 0, 0 1, 1 1, 1 0, 0 0)) )";\
  auto p28 = "MULTIPOLYGON ( ((0 0, 0 1, 1 1, 1 0, 0 0)), ((0 0, 0 4, 4 4, 4 0, 0 0)) )";\
  \
  auto p29 = "MULTIPOLYGON ( ((0 0, 1 0, 1 1, 0 0)), ((0 0, 1 4, 1 0, 0 0)) )";\
  auto p30 = "MULTIPOLYGON ( ((0 0, 0 4, 4 4, 0 0)), ((0 0, 1 -8, 1 1, 0 1, 0 0)) )";\
  auto p31 = "MULTIPOLYGON ( ((0 0, 1 -8, 1 1, 0 1, 0 0)), ((0 0, 4 4, 0 4, 0 0)) )";\
  auto p32 = "MULTIPOLYGON ( ((0 0, 1 -8, 1 1, 0 1, 0 0)), ((0 0, 4 4, 0 4, 0 0)),((0 0, 0 -2, -3 4, 0 2, 0 0)) )";\
  auto p33 = "MULTIPOLYGON ( ((0 0, 1 -8, 1 1, 0 1, 0 0)), ((0 0, 4 4, 0 4, 0 0)),((0 0, 0 -2, 3 4, 0 2, 0 0)) )";\


#define construct_common_test_cases_array\
	  arrow::StringBuilder builder;\
  std::shared_ptr<arrow::Array> input;\
  builder.Append(std::string(p1  ));\
  builder.Append(std::string(p2 ));\
  builder.Append(std::string(p3 ));\
  builder.Append(std::string(p4 ));\
  builder.Append(std::string(p5 ));\
  builder.Append(std::string(p6 ));\
  builder.Append(std::string(p7 ));\
  builder.Append(std::string(p8 ));\
  builder.Append(std::string(p9 ));\
  builder.Append(std::string(p10 ));\
  builder.Append(std::string(p11 ));\
  builder.Append(std::string(p12 ));\
  builder.Append(std::string(p13 ));\
  builder.Append(std::string(p14 ));\
  builder.Append(std::string(p15 ));\
  builder.Append(std::string(p16 ));\
  builder.Append(std::string(p17 ));\
  builder.Append(std::string(p18 ));\
  builder.Append(std::string(p19 ));\
  builder.Append(std::string(p20 ));\
  builder.Append(std::string(p21 ));\
  builder.Append(std::string(p22 ));\
  builder.Append(std::string(p23 ));\
  builder.Append(std::string(p24 ));\
  builder.Append(std::string(p25 ));\
  builder.Append(std::string(p26 ));\
  builder.Append(std::string(p27 ));\
  builder.Append(std::string(p28 ));\
  builder.Append(std::string(p29 ));\
  builder.Append(std::string(p30 ));\
  builder.Append(std::string(p31));\
  builder.Append(std::string(p32));\
  builder.Append(std::string(p33));\
  builder.Finish(&input);

TEST(geometry_test, make_point_from_double){

  arrow::DoubleBuilder builder_x;
  arrow::DoubleBuilder builder_y;
  std::shared_ptr<arrow::Array> ptr_x;
  std::shared_ptr<arrow::Array> ptr_y;

  for (int i = 0; i < 2; i++) {
    builder_x.Append(i);
    builder_y.Append(i);
  }

  builder_x.Finish(&ptr_x);
  builder_y.Finish(&ptr_y);

  auto point_arr = ST_Point(ptr_x,ptr_y);
  auto point_arr_str = std::static_pointer_cast<arrow::StringArray>(point_arr);

  ASSERT_EQ(point_arr_str->length(),2);
  ASSERT_EQ(point_arr_str->GetString(0),"POINT (0 0)");
  ASSERT_EQ(point_arr_str->GetString(1),"POINT (1 1)");
}


char*
build_point(double x, double y){

  OGRPoint point(x,y);
  char *point_str = nullptr;
  CHECK_GDAL(point.exportToWkt(&point_str));
  return point_str;
}

char*
build_polygon(double x, double y){

  OGRLinearRing ring;
  ring.addPoint(x, y);
  ring.addPoint(x, y+10);
  ring.addPoint(x+10, y+10);
  ring.addPoint(x+10, y);
  ring.addPoint(x, y);
  ring.closeRings();
  OGRPolygon polygon;
  polygon.addRing(&ring);

  char *polygon_str = nullptr;
  CHECK_GDAL(polygon.exportToWkt(&polygon_str));
  return polygon_str;
}

char*
build_linestring(double x, double y){

  OGRLineString line;
  line.addPoint(x, y);
  line.addPoint(x, y+20);

  char *line_str = nullptr;
  CHECK_GDAL(line.exportToWkt(&line_str));
  return line_str;
}

std::shared_ptr<arrow::Array> 
build_points(){

  arrow::StringBuilder string_builder;
  std::shared_ptr<arrow::Array> points;

  char *point_str1 = build_point(10,20);
  char *point_str2 = build_point(20,30);
  char *point_str3 = build_point(30,40);

  string_builder.Append(std::string(point_str1));
  string_builder.Append(std::string(point_str2));
  string_builder.Append(std::string(point_str3));

  CPLFree(point_str1);
  CPLFree(point_str2);
  CPLFree(point_str3);

  string_builder.Finish(&points);
  return points;
}

std::shared_ptr<arrow::Array> 
build_polygons(){

  arrow::StringBuilder string_builder;
  std::shared_ptr<arrow::Array> polygons;

  char *str1 = build_polygon(10,20);
  char *str2 = build_polygon(30,40);
  char *str3 = build_polygon(50,60);
  string_builder.Append(std::string(str1));
  string_builder.Append(std::string(str2));
  string_builder.Append(std::string(str3));
  CPLFree(str1);
  CPLFree(str2);
  CPLFree(str3);

  string_builder.Finish(&polygons);
  return polygons;
}

std::shared_ptr<arrow::Array> 
build_linestrings(){

  arrow::StringBuilder string_builder;
  std::shared_ptr<arrow::Array> line_strings;

  char *str1 = build_linestring(10,20);
  char *str2 = build_linestring(30,40);
  char *str3 = build_linestring(50,60);
  string_builder.Append(std::string(str1));
  string_builder.Append(std::string(str2));
  string_builder.Append(std::string(str3));
  CPLFree(str1);
  CPLFree(str2);
  CPLFree(str3);

  string_builder.Finish(&line_strings);
  return line_strings;
}

TEST(geometry_test,test_ST_IsValid){

  common_test_cases
  construct_common_test_cases_array
  auto res = ST_IsValid(input);
  auto res_bool = std::static_pointer_cast<arrow::BooleanArray>(res);
  for(int i=0;i<res_bool->length();i++){
   std::cout<<res_bool->Value(i)<<"#"<<i<<std::endl;
  }
   ASSERT_EQ(res_bool->Value(0),true);
   ASSERT_EQ(res_bool->Value(1),true);
   ASSERT_EQ(res_bool->Value(2),true);
   ASSERT_EQ(res_bool->Value(3),true);
   ASSERT_EQ(res_bool->Value(4),true);
   ASSERT_EQ(res_bool->Value(5),true);
   ASSERT_EQ(res_bool->Value(6),true);
   ASSERT_EQ(res_bool->Value(7),true);
   ASSERT_EQ(res_bool->Value(8),true);
   ASSERT_EQ(res_bool->Value(9),true);
   ASSERT_EQ(res_bool->Value(10),true);
   ASSERT_EQ(res_bool->Value(11),true);
   ASSERT_EQ(res_bool->Value(12),true);
   ASSERT_EQ(res_bool->Value(13),true);
   ASSERT_EQ(res_bool->Value(14),true);
   ASSERT_EQ(res_bool->Value(15),true);
   ASSERT_EQ(res_bool->Value(16),true);
   ASSERT_EQ(res_bool->Value(17),true);
   ASSERT_EQ(res_bool->Value(18),false);
   ASSERT_EQ(res_bool->Value(19),false);
   ASSERT_EQ(res_bool->Value(20),false);
   ASSERT_EQ(res_bool->Value(21),false);
   ASSERT_EQ(res_bool->Value(22),false);
   ASSERT_EQ(res_bool->Value(23),false);
   ASSERT_EQ(res_bool->Value(24),false);
   ASSERT_EQ(res_bool->Value(25),false);
   ASSERT_EQ(res_bool->Value(26),false);
   ASSERT_EQ(res_bool->Value(27),false);
   ASSERT_EQ(res_bool->Value(28),false);
   ASSERT_EQ(res_bool->Value(29),false);
   ASSERT_EQ(res_bool->Value(30),false);
   ASSERT_EQ(res_bool->Value(31),false);
   ASSERT_EQ(res_bool->Value(32),false);
}

TEST(geometry_test, test_ST_Intersection){

  arrow::StringBuilder left_string_builder;
  std::shared_ptr<arrow::Array> left_geometry;
  arrow::StringBuilder right_string_builder;
  std::shared_ptr<arrow::Array> right_geometry;
  char *left_str = nullptr;
  char *right_str = nullptr;

  left_str = build_point(25,25);
  right_str = build_polygon(20,20);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection1 = ST_Intersection(left_geometry,right_geometry);
  // auto intersection_polygons_arr = std::static_pointer_cast<arrow::StringArray>(intersection_polygons);
  // ASSERT_EQ(intersection_polygons_arr->GetString(0),"LINESTRING (20 30, 20 20)");

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_polygon(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection2 = ST_Intersection(left_geometry,right_geometry);

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_point(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection3 = ST_Intersection(left_geometry,right_geometry);
  
  CPLFree(left_str);
  CPLFree(right_str);
}

// TEST(geometry_test, test_ST_PrecisionReduce){
//   OGRPoint point(1.5555555,1.55555555);
//   arrow::StringBuilder string_builder;
//   std::shared_ptr<arrow::Array> array;
  
//   char *str = nullptr;
//   CHECK_GDAL(point.exportToWkt(&str));
//   string_builder.Append(std::string(str));
//   CPLFree(str);

//   string_builder.Finish(&array);
//   auto geometries = ST_PrecisionReduce(array,6);
//   auto geometries_arr = std::static_pointer_cast<arrow::StringArray>(geometries);
  
//   // ASSERT_EQ(geometries_arr->GetString(0),"POINT (1.55556 1.55556)");
//   ASSERT_EQ(geometries_arr->GetString(0),"POINT (1.5555555 1.55555555)");
// }

TEST(geometry_test, test_ST_Equals){
  arrow::StringBuilder left_string_builder;
  std::shared_ptr<arrow::Array> left_geometry;
  arrow::StringBuilder right_string_builder;
  std::shared_ptr<arrow::Array> right_geometry;
  char *left_str = nullptr;
  char *right_str = nullptr;

  left_str = build_point(25,25);
  right_str = build_polygon(20,20);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection1 = ST_Equals(left_geometry,right_geometry);
  // auto intersection_polygons_arr = std::static_pointer_cast<arrow::StringArray>(intersection_polygons);
  // ASSERT_EQ(intersection_polygons_arr->GetString(0),"LINESTRING (20 30, 20 20)");

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_polygon(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection2 = ST_Equals(left_geometry,right_geometry);

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_point(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection3 = ST_Equals(left_geometry,right_geometry);
  
  CPLFree(left_str);
  CPLFree(right_str);
}

TEST(geometry_test, test_ST_Touches){
  arrow::StringBuilder left_string_builder;
  std::shared_ptr<arrow::Array> left_geometry;
  arrow::StringBuilder right_string_builder;
  std::shared_ptr<arrow::Array> right_geometry;
  char *left_str = nullptr;
  char *right_str = nullptr;

  left_str = build_point(25,25);
  right_str = build_polygon(20,20);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection1 = ST_Touches(left_geometry,right_geometry);
  // auto intersection_polygons_arr = std::static_pointer_cast<arrow::StringArray>(intersection_polygons);
  // ASSERT_EQ(intersection_polygons_arr->GetString(0),"LINESTRING (20 30, 20 20)");

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_polygon(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection2 = ST_Touches(left_geometry,right_geometry);

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_point(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection3 = ST_Touches(left_geometry,right_geometry);
  
  CPLFree(left_str);
  CPLFree(right_str);
}

TEST(geometry_test, test_ST_Overlaps){
  arrow::StringBuilder left_string_builder;
  std::shared_ptr<arrow::Array> left_geometry;
  arrow::StringBuilder right_string_builder;
  std::shared_ptr<arrow::Array> right_geometry;
  char *left_str = nullptr;
  char *right_str = nullptr;

  left_str = build_point(25,25);
  right_str = build_polygon(20,20);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection1 = ST_Overlaps(left_geometry,right_geometry);
  // auto intersection_polygons_arr = std::static_pointer_cast<arrow::StringArray>(intersection_polygons);
  // ASSERT_EQ(intersection_polygons_arr->GetString(0),"LINESTRING (20 30, 20 20)");

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_polygon(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection2 = ST_Overlaps(left_geometry,right_geometry);

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_point(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection3 = ST_Overlaps(left_geometry,right_geometry);
  
  CPLFree(left_str);
  CPLFree(right_str);
}


TEST(geometry_test, test_ST_Crosses){
  arrow::StringBuilder left_string_builder;
  std::shared_ptr<arrow::Array> left_geometry;
  arrow::StringBuilder right_string_builder;
  std::shared_ptr<arrow::Array> right_geometry;
  char *left_str = nullptr;
  char *right_str = nullptr;

  left_str = build_point(25,25);
  right_str = build_polygon(20,20);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection1 = ST_Crosses(left_geometry,right_geometry);
  // auto intersection_polygons_arr = std::static_pointer_cast<arrow::StringArray>(intersection_polygons);
  // ASSERT_EQ(intersection_polygons_arr->GetString(0),"LINESTRING (20 30, 20 20)");

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_polygon(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection2 = ST_Crosses(left_geometry,right_geometry);

  left_string_builder.Reset();
  right_string_builder.Reset();

  left_str = build_point(20,20);
  right_str = build_linestring(25,25);
  left_string_builder.Append(std::string(left_str));
  right_string_builder.Append(std::string(right_str));
  left_string_builder.Finish(&left_geometry);
  right_string_builder.Finish(&right_geometry);
  auto intersection3 = ST_Crosses(left_geometry,right_geometry);
  
  CPLFree(left_str);
  CPLFree(right_str);
}


TEST(geometry_test, test_ST_IsSimple){
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_IsSimple(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_IsSimple(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> line = build_linestrings();
  auto vaild_mark3 = ST_IsSimple(line);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
}

TEST(geometry_test, test_ST_MakeValid){
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> line = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(line);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
}

TEST(geometry_test, test_ST_GeometryType){
  OGRLinearRing ring1;
  ring1.addPoint(2, 1);
  ring1.addPoint(3, 1);
  ring1.addPoint(3, 2);
  ring1.addPoint(2, 2);
  ring1.addPoint(2, 8);
  ring1.closeRings();
  OGRPolygon polygon1;
  polygon1.addRing(&ring1);

  OGRPoint point(2,3);
  OGRLineString line;
  line.addPoint(10,20);
  line.addPoint(20,30);

  arrow::StringBuilder string_builder;
  std::shared_ptr<arrow::Array> geometries;

  char *polygon_str = nullptr;
  char *point_str = nullptr;
  char *line_str = nullptr;
  CHECK_GDAL(polygon1.exportToWkt(&polygon_str));
  CHECK_GDAL(point.exportToWkt(&point_str));
  CHECK_GDAL(line.exportToWkt(&line_str));
  string_builder.Append(std::string(polygon_str));
  string_builder.Append(std::string(point_str));
  string_builder.Append(std::string(line_str));
  CPLFree(polygon_str);
  CPLFree(point_str);
  CPLFree(line_str);

  string_builder.Finish(&geometries);

  auto geometries_type = ST_GeometryType(geometries);
  auto geometries_type_arr = std::static_pointer_cast<arrow::StringArray>(geometries_type);
  
  ASSERT_EQ(geometries_type_arr->GetString(0),"POLYGON");
  ASSERT_EQ(geometries_type_arr->GetString(1),"POINT");
  ASSERT_EQ(geometries_type_arr->GetString(2),"LINESTRING");
}

TEST(geometry_test, test_ST_SimplifyPreserveTopology){
  OGRLinearRing ring1;
  ring1.addPoint(2, 1);
  ring1.addPoint(3, 1);
  ring1.addPoint(3, 2);
  ring1.addPoint(2, 2);
  ring1.addPoint(2, 8);
  ring1.closeRings();
  OGRPolygon polygon1;
  polygon1.addRing(&ring1);

  OGRPoint point(2,3);
  OGRLineString line;
  line.addPoint(10,20);
  line.addPoint(20,30);

  arrow::StringBuilder string_builder;
  std::shared_ptr<arrow::Array> geometries;

  char *polygon_str = nullptr;
  char *point_str = nullptr;
  char *line_str = nullptr;
  CHECK_GDAL(polygon1.exportToWkt(&polygon_str));
  CHECK_GDAL(point.exportToWkt(&point_str));
  CHECK_GDAL(point.exportToWkt(&line_str));
  string_builder.Append(std::string(polygon_str));
  string_builder.Append(std::string(point_str));
  string_builder.Append(std::string(line_str));
  CPLFree(polygon_str);
  CPLFree(point_str);
  CPLFree(line_str);

  string_builder.Finish(&geometries);

  auto geometries_arr = ST_SimplifyPreserveTopology(geometries,10000);
  auto geometries_arr_str = std::static_pointer_cast<arrow::StringArray>(geometries_arr);
  
  ASSERT_EQ(geometries_arr_str->GetString(0),"POLYGON ((2 1,3 1,2 8,2 1))");
  ASSERT_EQ(geometries_arr_str->GetString(1),"POINT (2 3)");
//  ASSERT_EQ(geometries_arr_str->GetString(2),"LINESTRING");

}

TEST(geometry_test, test_ST_Contains) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Contains(points, polygons);
  auto res2 = ST_Contains(polygons, lines);
  auto res3 = ST_Contains(points, lines);
}

TEST(geometry_test, test_ST_Intersects) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Intersects(points, polygons);
  auto res2 = ST_Intersects(polygons, lines);
  auto res3 = ST_Intersects(points, lines);
}

TEST(geometry_test, test_ST_Within) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Within(points, polygons);
  auto res2 = ST_Within(polygons, lines);
  auto res3 = ST_Within(points, lines);
}

TEST(geometry_test, test_ST_Distance) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Distance(points, polygons);
  auto res2 = ST_Distance(polygons, lines);
  auto res3 = ST_Distance(points, lines);
}

TEST(geometry_test, test_ST_Area) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Area(points);
  auto res2 = ST_Area(polygons);
  auto res3 = ST_Area(lines);
}

TEST(geometry_test, test_ST_Centroid) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Centroid(points);
  auto res2 = ST_Centroid(polygons);
  auto res3 = ST_Centroid(lines);
}

TEST(geometry_test, test_ST_Length) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Length(points);
  auto res2 = ST_Length(polygons);
  auto res3 = ST_Length(lines);
}

TEST(geometry_test, test_ST_ConvexHull) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_ConvexHull(points);
  auto res2 = ST_ConvexHull(polygons);
  auto res3 = ST_ConvexHull(lines);
}

//TODO:geospark ST_NPoints can not work.
TEST(geometry_test, test_ST_NPoints) {
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_NPoints(points);
  auto res2 = ST_NPoints(polygons);
  auto res3 = ST_NPoints(lines);
}

TEST(geometry_test, test_ST_Envelope) {
   common_test_cases
   construct_common_test_cases_array

  auto result = ST_Envelope(input);
  auto result_str = std::static_pointer_cast<arrow::StringArray>(result);

  for(int i=0;i<result_str->length();i++){
   std::cout<<result_str->GetString(i)<<"#"<<i<<std::endl;
  }
   ASSERT_EQ(result_str->GetString(0),"POINT (0 1)");
   ASSERT_EQ(result_str->GetString(1),"LINESTRING (0 0,0 1)");
   ASSERT_EQ(result_str->GetString(2),"LINESTRING (0 0,1 0)");
   ASSERT_EQ(result_str->GetString(3),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(4),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(5),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(6),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(7),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(8),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(9),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(10),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(11),"POLYGON ((0 0,0 2,1 2,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(12),"POLYGON ((0 0,0 2,1 2,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(13),"POLYGON ((0 0,0 2,1 2,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(14),"POLYGON ((0 0,0 2,1 2,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(15),"POLYGON ((-4 -3,-4 100,9 100,9 -3,-4 -3))");
   ASSERT_EQ(result_str->GetString(16),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(17),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(18),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   //ASSERT_EQ(result_str->GetString(19),"POLYGON ((0 0,0 1,4 1,4 0,0 0))");
   //ASSERT_EQ(result_str->GetString(20),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(21),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   //ASSERT_EQ(result_str->GetString(22),"POLYGON ((0 0,0 1,4 1,4 0,0 0))");
   //ASSERT_EQ(result_str->GetString(23),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   ASSERT_EQ(result_str->GetString(24),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   ASSERT_EQ(result_str->GetString(25),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   ASSERT_EQ(result_str->GetString(26),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   ASSERT_EQ(result_str->GetString(27),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   //ASSERT_EQ(result_str->GetString(28),"POLYGON ((0 0,0 1,1 1,1 0,0 0))");
   //ASSERT_EQ(result_str->GetString(29),"POLYGON ((0 0,0 4,4 4,4 0,0 0))");
   ASSERT_EQ(result_str->GetString(30),"POLYGON ((0 -8,0 4,4 4,4 -8,0 -8))");
   //ASSERT_EQ(result_str->GetString(31),"POLYGON ((0 -8,0 4,4 4,4 -8,0 -8))");
   ASSERT_EQ(result_str->GetString(32),"POLYGON ((0 -8,0 4,4 4,4 -8,0 -8))");

}

TEST(geometry_test, test_ST_Buffer){
  std::shared_ptr<arrow::Array> points = build_points();
  auto vaild_mark1 = ST_MakeValid(points);
  auto vaild_mark_arr1 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark1);

  std::shared_ptr<arrow::Array> polygons = build_polygons();
  auto vaild_mark2 = ST_MakeValid(polygons);
  auto vaild_mark_arr2 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark2);

  std::shared_ptr<arrow::Array> lines = build_linestrings();
  auto vaild_mark3 = ST_MakeValid(lines);
  auto vaild_mark_arr3 = std::static_pointer_cast<arrow::BooleanArray>(vaild_mark3);
  
  auto res1 = ST_Buffer(points,1.2);
  auto res2 = ST_Buffer(polygons,1.2);
  auto res3 = ST_Buffer(lines,1.2);
}

TEST(geometry_test, test_ST_PolygonFromEnvelope){
  arrow::DoubleBuilder x_min;
  arrow::DoubleBuilder x_max;
  arrow::DoubleBuilder y_min;
  arrow::DoubleBuilder y_max;

  x_min.Append(0);
  x_max.Append(1);
  y_min.Append(0);
  y_max.Append(1);

  std::shared_ptr<arrow::Array> x_min_ptr;
  std::shared_ptr<arrow::Array> x_max_ptr;
  std::shared_ptr<arrow::Array> y_min_ptr;
  std::shared_ptr<arrow::Array> y_max_ptr;

  x_min.Finish(&x_min_ptr);
  x_max.Finish(&x_max_ptr);
  y_min.Finish(&y_min_ptr);
  y_max.Finish(&y_max_ptr);

  auto res = ST_PolygonFromEnvelope(x_min_ptr, y_min_ptr, x_max_ptr,y_max_ptr);

  auto res_str = std::static_pointer_cast<arrow::StringArray>(res)->GetString(0);
  std::string expect = "POLYGON ((0 0,1 0,0 1,1 1,0 0))";

  ASSERT_EQ(res_str,expect);
}

TEST(geometry_test,test_ST_Transform){
  arrow::StringBuilder builder;
  std::shared_ptr<arrow::Array> input_data;

  builder.Append(std::string("POINT (10 10)"));
  builder.Finish(&input_data);
  std::string src_rs("EPSG:4326");
  std::string dst_rs("EPSG:3857");

  auto res = ST_Transform(input_data,src_rs,dst_rs);
  auto res_str = std::static_pointer_cast<arrow::StringArray>(res)->GetString(0);
  OGRGeometry *res_geo = nullptr;
  CHECK_GDAL(OGRGeometryFactory::createFromWkt(res_str.c_str(),nullptr,&res_geo));

  auto rst_pointer = reinterpret_cast<OGRPoint*>(res_geo);

  ASSERT_DOUBLE_EQ(rst_pointer->getX(),1113194.90793274);
  ASSERT_DOUBLE_EQ(rst_pointer->getY(),1118889.97485796);

  OGRGeometryFactory::destroyGeometry(res_geo);
}

TEST(geometry_test,test_ST_Union_Aggr){
  arrow::StringBuilder builder;
  std::shared_ptr<arrow::Array> polygons;

  auto p1 = "POLYGON ((1 1,1 2,2 2,2 1,1 1))";
  auto p2 = "POLYGON ((2 1,3 1,3 2,2 2,2 1))";
  builder.Reset();
  builder.Append(std::string(p1));
  builder.Append(std::string(p2));
  builder.Finish(&polygons);

  auto result = ST_Union_Aggr(polygons);
  auto geometries_arr = std::static_pointer_cast<arrow::StringArray>(result);

  ASSERT_EQ(geometries_arr->GetString(0),"POLYGON ((1 1,1 2,2 2,3 2,3 1,2 1,1 1))");


  p1 = "POLYGON ((0 0,4 0,4 4,0 4,0 0))";
  p2 = "POLYGON ((3 1,5 1,5 2,3 2,3 1))";
  builder.Reset();
  builder.Append(std::string(p1));
  builder.Append(std::string(p2));
  builder.Finish(&polygons);
  result = ST_Union_Aggr(polygons);
  geometries_arr = std::static_pointer_cast<arrow::StringArray>(result);

  ASSERT_EQ(geometries_arr->GetString(0),"POLYGON ((4 1,4 0,0 0,0 4,4 4,4 2,5 2,5 1,4 1))");

  p1 = "POLYGON ((0 0,4 0,4 4,0 4,0 0))";
  p2 = "POLYGON ((5 1,7 1,7 2,5 2,5 1))";
  builder.Reset();
  builder.Append(std::string(p1));
  builder.Append(std::string(p2));
  builder.Finish(&polygons);
  result = ST_Union_Aggr(polygons);
  geometries_arr = std::static_pointer_cast<arrow::StringArray>(result);

  ASSERT_EQ(geometries_arr->GetString(0),"MULTIPOLYGON (((0 0,4 0,4 4,0 4,0 0)),((5 1,7 1,7 2,5 2,5 1)))");

  p1 = "POLYGON ((0 0,4 0,4 4,0 4,0 0))";
  p2 = "POINT (2 3)";
  builder.Reset();
  builder.Append(std::string(p1));
  builder.Append(std::string(p2));
  builder.Finish(&polygons);
  result = ST_Union_Aggr(polygons);
  geometries_arr = std::static_pointer_cast<arrow::StringArray>(result);

  ASSERT_EQ(geometries_arr->GetString(0), "POLYGON ((0 0,0 4,4 4,4 0,0 0))");


}


TEST(geometry_test,test_ST_Envelope_Aggr){

  arrow::StringBuilder builder;
  std::shared_ptr<arrow::Array> polygons;

  auto p1 = "POLYGON ((0 0,4 0,4 4,0 4,0 0))";
  auto p2 = "POLYGON ((5 1,7 1,7 2,5 2,5 1))";
  builder.Reset();
  builder.Append(std::string(p1));
  builder.Append(std::string(p2));
  builder.Finish(&polygons);

  auto result = ST_Envelope_Aggr(polygons);
  auto geometries_arr = std::static_pointer_cast<arrow::StringArray>(result);

  ASSERT_EQ(geometries_arr->GetString(0),"POLYGON ((0 0,7 0,7 4,0 4,0 0))");

}
