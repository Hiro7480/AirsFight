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
 18;
 40.000000;5.426504;0.000000;,
 12.360680;5.426504;38.042259;,
 -32.360680;5.426504;23.511410;,
 -32.360680;5.426504;-23.511410;,
 12.360680;5.426504;-38.042259;,
 32.000000;22.894135;0.000000;,
 9.888544;22.894135;30.433807;,
 -25.888544;22.894135;18.809128;,
 -25.888544;22.894135;-18.809128;,
 9.888544;22.894135;-30.433807;,
 0.000000;-24.568331;0.000000;,
 -32.360680;5.426504;23.511410;,
 -25.888544;22.894135;18.809128;,
 32.000000;22.894135;0.000000;,
 9.888544;22.894135;-30.433807;,
 -25.888544;22.894135;-18.809128;,
 -25.888544;22.894135;18.809128;,
 9.888544;22.894135;30.433807;;

 11;
 3;4,0,10;,
 3;4,10,3;,
 3;10,0,1;,
 3;10,2,3;,
 3;2,10,1;,
 4;5,6,1,0;,
 4;6,7,11,1;,
 4;12,8,3,2;,
 4;8,9,4,3;,
 4;9,5,0,4;,
 5;13,14,15,16,17;;

 MeshMaterialList {
  2;
  11;
  0,0,0,0,0,0,0,0,0,0,1;;
  {MatDefault}
  {MatYWall}
 }
 MeshNormals {
  11;
  0.549961;-0.733408;-0.399570;,
  -0.210066;-0.733408;-0.646518;,
  0.549961;-0.733408;0.399570;,
  -0.679789;-0.733408;0.000000;,
  -0.210066;-0.733408;0.646518;,
  0.758617;0.347439;0.551168;,
  -0.289766;0.347439;0.891808;,
  -0.937703;0.347439;0.000000;,
  -0.289766;0.347439;-0.891808;,
  0.758617;0.347439;-0.551168;,
  0.000000;1.000000;0.000000;;

  11;
  3;0,0,0;,
  3;1,1,1;,
  3;2,2,2;,
  3;3,3,3;,
  3;4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  5;10,10,10,10,10;;
 }
 MeshTextureCoords {
  18;
  0.750000;0.457079;
  0.950000;0.457079;
  0.150000;0.457079;
  0.350000;0.457079;
  0.550000;0.457079;
  0.750000;0.302325;
  0.950000;0.302325;
  1.150000;0.302325;
  0.350000;0.302325;
  0.550000;0.302325;
  0.500000;1.000000;
  1.150000;0.457079;
  0.150000;0.302325;
  0.651162;0.500000;
  0.564891;0.781487;
  0.365243;0.658652;
  0.365243;0.341348;
  0.564891;0.218513;;
 }
}
