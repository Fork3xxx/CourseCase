package com.example.dynamicfragmentdemo;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;


public class MainActivity extends AppCompatActivity {


    private Fragment_Container fragment1;
    private Fragment_Container fragment2;
    private Fragment_Container fragment3;
    private FragmentManager fragmentManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //创建不同的Fragment实例
        fragment1 = new Fragment_Container(1);
        fragment2 = new Fragment_Container(2);
        fragment3 = new Fragment_Container(3);
        //获取fragment管理器
        fragmentManager = getFragmentManager();

        //加载默认的fragment,这里将选择第一个fragment作为默认的
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.add(R.id.fl_container,fragment1);
        fragmentTransaction.commit();//一定要提交


    }
    //点击Button执行的方法
    public void onClick(View view){
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        if (view.getId() == R.id.btn_add) {
            fragmentTransaction.add(R.id.fl_container,fragment1);
        }else if (view.getId() == R.id.btn_remove){
            fragmentTransaction.remove(fragment2);
        }else if (view.getId() == R.id.btn_replace){
            fragmentTransaction.replace(R.id.fl_container,fragment1);
        }else if (view.getId() == R.id.btn_hide){
            fragmentTransaction.hide(fragment3);
        }else if (view.getId() == R.id.btn_show){
            fragmentTransaction.show(fragment1);
        }
        fragmentTransaction.commit();//一定要提交

    }
}
