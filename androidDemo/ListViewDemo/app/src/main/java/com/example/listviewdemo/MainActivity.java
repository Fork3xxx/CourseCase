package com.example.listviewdemo;

import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private ListView listView;
    private ArrayList<String> data;
    private ArrayAdapter<String> adapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //初始化数据
        initData();
        listView = findViewById(R.id.lv_name);

        adapter = new ArrayAdapter<>(this,android.R.layout.simple_list_item_1,data);
        //为listview设置适配器
        listView.setAdapter(adapter);

        //为了listview设置点击item侦听器
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                 final int p = position;
//                String name=data[position];
//                String msg ="你点击了："+data.get(position);
////                Toast.makeText(MainActivity.this,msg,Toast.LENGTH_SHORT).show();
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                builder.setTitle("提示");
                builder.setMessage("确认删除吗？");
                builder.setIcon(R.mipmap.ic_launcher);
                builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        deletedata(p);
                    }
                });
                builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
                builder.create().show();
//                    showDialog();
//                  Toast.makeText(MainActivity.this,"你已删除",Toast.LENGTH_SHORT,null).show();

            }
        });




        //为listview增加footer
        View footer = LayoutInflater.from(this).inflate(R.layout.listview_footer,null);
        listView.addFooterView(footer);
        //设置显示位置
        listView.setSelection(data.size()-1);
        //为 footer设置点击事件侦听器
        footer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //为listview增加一行数据
                //首先给data增加数据
                data.add("这是点击footer增加的item");
                //然后通知listview数据有改变
                adapter.notifyDataSetChanged();
            }
        });
    }


    //删除listview指定行,其中position是指定行的行号
    private void deletedata(int position){
        //首先删除data里面对应的数据
        data.remove(position);
        //然后通知listview数据有改变
        adapter.notifyDataSetChanged();

    }
    private void initData(){
        data = new ArrayList<String>();
        String[] name = getResources().getStringArray(R.array.lv_name);
        for (int i = 0; i < name.length; i++){
            data.add(name[i]);
        }
    }

    //显示对话框
//    protected void showDialog(){
//        AlertDialog.Builder builder = new AlertDialog.Builder(this);
//        builder.setTitle("提示");
//        builder.setMessage("确认删除吗？");
//        builder.setIcon(R.mipmap.ic_launcher);
//        builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
//            @Override
//            public void onClick(DialogInterface dialog, int which) {
//                deletedata(position);
//            }
//        });
//        builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
//            @Override
//            public void onClick(DialogInterface dialog, int which) {
//                dialog.dismiss();
//            }
//        });
//        builder.create().show();
    }




