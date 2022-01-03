#ifndef STLFILELOADER_H
#define STLFILELOADER_H

#include <QList>
#include <QVector3D>

class STLTriangle;

//STL文件解析类
class STLFileLoader {
public:
    /**
   * @brief STLFileLoader
   * @param filename  stl文件路径
   * @param ratio  放大系数（有的3d模型单位很小，通过放大系数将模型放大）
   */
  STLFileLoader(QString filename, int ratio);
  ~STLFileLoader();
  /**
   * @brief draw  画出STL模型
   */
  void draw();

private:
  /**
   * @brief loadStl  加载stl文件
   * @param filename
   */
  void loadStl(QString filename);
  /**
   * @brief loadTextStl 加载文本格式stl文件
   * @param filename
   */
  void loadTextStl(QString filename);
  /**
   * @brief loadBinaryStl 加载二进制格式stl文件
   * @param filename
   */
  void loadBinaryStl(QString filename);

private:
  QList<STLTriangle> model;
  int mRatio = 1; //比例系数
};

//stl格式： 三个顶点 + 法向量
class STLTriangle {
public:
  STLTriangle();
  /**
   * @brief setVertex  设置顶点坐标
   * @param index  哪个点
   * @param point3D
   */
  void setVertex(int index, QVector3D point3D);
  /**
   * @brief getVertex  获取顶点坐标
   * @param index 哪个点
   * @return
   */
  QVector3D getVertex(int index);
  /**
   * @brief setNormal 设置法向量
   * @param nx    x分量
   * @param ny    y分量
   * @param nz    z分量
   */
  void setNormal(float nx, float ny, float nz);
  /**
   * @brief getNormal  获取法向量
   * @return
   */
  QVector3D getNormal();
  /**
   * @brief reset 重置参数
   */
  void reset();

private:
  /**
   * @brief checkVertexIndex
   * @param index
   * @return
   */
  bool checkVertexIndex(int index);

private:
  QVector3D v[3]; //三角顶点坐标
  QVector3D n;    //三角形法向量的三个分量
};

#endif // STLFILELOADER_H
