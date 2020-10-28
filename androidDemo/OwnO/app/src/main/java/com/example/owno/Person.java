package com.example.owno;
//用来描述listview的item的数据类型
public class Person {
    private String name;   //姓名
    private int headImage;  //图像

    public Person(String name, int headImage) {
        this.name = name;
        this.headImage = headImage;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getHeadImage() {
        return headImage;
    }

    public void setHeadImage(int headImage) {
        this.headImage = headImage;
    }
}
