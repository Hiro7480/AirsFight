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
  "Taile2.png";
 }
}
Mesh {
 10;
 -8.667413;0.000000;-100.660683;,
 9.722844;0.000000;-100.660698;,
 9.722844;0.000000;100.660698;,
 -8.667413;0.000000;100.660713;,
 -8.667413;-5.000000;-100.660683;,
 9.722844;-5.000000;-100.660698;,
 9.722844;-5.000000;100.660698;,
 -8.667413;-5.000000;100.660713;,
 9.722844;-5.000000;100.660698;,
 -8.667413;-5.000000;100.660713;;

 6;
 4;0,3,2,1;,
 4;0,1,5,4;,
 4;1,2,6,5;,
 4;3,7,6,2;,
 4;0,4,7,3;,
 4;4,5,8,9;;

 MeshMaterialList {
  1;
  1;
  0;;
  {MatDefault}
 }
 MeshNormals {
  6;
  0.000000;1.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000001;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;;

  6;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  10;
  0.750000;0.527341;
  0.750000;0.469349;
  0.250000;0.469349;
  0.250000;0.527341;
  0.757899;0.527307;
  0.757899;0.469387;
  0.242101;0.469387;
  0.242101;0.527307;
  1.242101;0.469387;
  1.242101;0.527307;;
 }
}
