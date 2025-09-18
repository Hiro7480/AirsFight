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

Material MatDefault {
 1.000000;1.000000;1.000000;1.000000;;
 21.333333;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
 TextureFilename {
  "Taile.png";
 }
}
Mesh {
 20;
 -40.000000;0.000000;-20.000000;,
 -40.000000;40.000000;40.000000;,
 -40.000000;40.000000;-20.000000;,
 -40.000000;0.000000;40.000000;,
 20.000000;0.000000;-20.000000;,
 20.000000;40.000000;40.000000;,
 20.000000;40.000000;-20.000000;,
 20.000000;0.000000;40.000000;,
 20.000000;0.000000;-30.000000;,
 -40.000000;40.000000;-30.000000;,
 -20.001684;40.000000;-30.000000;,
 20.000000;40.000000;20.001684;,
 -40.000000;0.000000;-30.000000;,
 30.000000;0.000000;-20.000000;,
 30.000000;40.000000;40.000000;,
 30.000000;40.000000;20.001684;,
 -20.001684;40.000000;-20.000000;,
 30.000000;0.000000;40.000000;,
 -40.000000;0.000000;40.000000;,
 -40.000000;40.000000;40.000000;;

 13;
 4;4,7,5,11;,
 4;13,4,11,15;,
 4;15,11,5,14;,
 6;1,3,7,17,14,5;,
 4;13,15,14,17;,
 4;8,12,9,10;,
 4;4,8,10,16;,
 4;16,10,9,2;,
 6;18,19,2,9,12,0;,
 4;4,16,2,0;,
 4;4,0,2,6;,
 4;6,2,19,5;,
 4;4,6,5,7;;

 MeshMaterialList {
  1;
  1;
  0;;
  {MatDefault}
 }
 MeshNormals {
  13;
  -1.000000;0.000000;0.000000;,
  0.000000;0.707122;-0.707092;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707092;0.707122;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;;

  13;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  6;3,3,3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  6;8,8,8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;;
 }
 MeshTextureCoords {
  20;
  0.323792;0.500000;
  1.125000;0.304087;
  0.323792;0.267720;
  1.125000;0.500000;
  0.625000;0.500000;
  0.926208;0.267720;
  0.625000;0.195913;
  0.926208;0.500000;
  0.593584;0.500000;
  0.352416;0.285223;
  0.406410;0.233510;
  0.875007;0.195920;
  0.352416;0.500000;
  0.656416;0.500000;
  0.897584;0.285223;
  0.843590;0.233510;
  0.374993;0.195920;
  0.897584;0.500000;
  0.125000;0.500000;
  0.125000;0.304087;;
 }
}
