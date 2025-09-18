xof 0302txt 0064
// LWS2X generated file 
// (LWS2X (C)1996-1998 A.Koizuka/Bio_100%  mailto:koizuka@ss.iij4u.or.jp )
// http://www.ss.iij4u.or.jp/~koizuka/

template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header {
 1;
 0;
 1;
}

Material MatZWall {
 1.000000;1.000000;1.000000;1.000000;;
 21.333333;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
 TextureFilename {
  "Taile.png";
 }
}
Material MatXWall {
 1.000000;1.000000;1.000000;1.000000;;
 21.333333;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
 TextureFilename {
  "Taile.png";
 }
}
Material MatYWall {
 1.000000;1.000000;1.000000;1.000000;;
 21.333333;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
 TextureFilename {
  "Taile.png";
 }
}
Mesh {
 30;
 -50.000000;0.000000;50.000000;,
 50.000000;60.000000;-50.000000;,
 -50.000000;60.000000;50.000000;,
 50.000000;0.000000;-70.000000;,
 -50.000000;0.000000;-70.000000;,
 -30.000000;60.000000;-70.000000;,
 -30.000000;60.000000;-50.000000;,
 -50.000000;60.000000;-70.000000;,
 70.000000;0.000000;-50.000000;,
 70.000000;0.000000;50.000000;,
 50.000000;60.000000;30.000000;,
 70.000000;60.000000;30.000000;,
 70.000000;60.000000;50.000000;,
 -50.000000;0.000000;-50.000000;,
 50.000000;0.000000;-50.000000;,
 -50.000000;60.000000;-50.000000;,
 50.000000;0.000000;50.000000;,
 50.000000;60.000000;50.000000;,
 -50.000000;60.000000;-50.000000;,
 50.000000;60.000000;50.000000;,
 50.000000;60.000000;-50.000000;,
 -50.000000;60.000000;50.000000;,
 -30.000000;60.000000;-70.000000;,
 -50.000000;60.000000;-70.000000;,
 -30.000000;60.000000;-50.000000;,
 -50.000000;60.000000;50.000000;,
 -50.000000;0.000000;50.000000;,
 50.000000;60.000000;30.000000;,
 70.000000;60.000000;50.000000;,
 70.000000;60.000000;30.000000;;

 11;
 4;13,15,1,14;,
 4;14,1,17,16;,
 4;18,2,19,20;,
 4;3,5,6,14;,
 6;0,21,15,7,4,13;,
 4;3,4,7,5;,
 4;22,23,18,24;,
 4;14,10,11,8;,
 4;8,11,12,9;,
 6;25,26,16,9,12,17;,
 4;27,19,28,29;;

 MeshMaterialList {
  3;
  11;
  0,1,2,1,1,0,2,0,1,0,2;;
  {MatZWall}
  {MatXWall}
  {MatYWall}
 }
 MeshNormals {
  11;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.600000;0.800000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.800000;-0.600000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;;

  11;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  6;4,4,4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  6;9,9,9,9,9,9;,
  4;10,10,10,10;;
 }
 MeshTextureCoords {
  30;
  0.125000;0.500000;
  0.625000;0.276025;
  0.389429;0.318740;
  0.598716;0.500000;
  0.401284;0.500000;
  0.435559;0.287598;
  0.413990;0.245452;
  0.401284;0.306138;
  0.651284;0.500000;
  0.848716;0.500000;
  0.836010;0.245452;
  0.814441;0.287598;
  0.848716;0.306138;
  0.375000;0.500000;
  0.625000;0.500000;
  0.375000;0.276025;
  0.875000;0.500000;
  0.875000;0.276025;
  0.389429;0.681260;
  0.610571;0.318740;
  0.610571;0.681260;
  0.125000;0.276025;
  0.426208;0.756775;
  0.389429;0.732603;
  0.426208;0.703885;
  1.125000;0.276025;
  1.125000;0.500000;
  0.610571;0.383265;
  0.637219;0.341821;
  0.637219;0.399863;;
 }
}
