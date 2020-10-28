package com.example.owno;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class ListViewAdapter extends BaseAdapter {
    private ArrayList<Person> data;
    private Context context;

    public ListViewAdapter(ArrayList<Person>data, Context context){
        this.data = data;
        this.context = context;
    }

    @Override
    public int getCount() {
        return data.size();
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    //获取第position行的view
    public View getView(int position, View convertView, ViewGroup parent) {
        //先将item用的布局文件转化为view对象，然后为view里面的控件设置具体内容
        ViewHolder viewHolder;
//        View converView;
        if (convertView == null){
//            viewHolder = new ViewHolder();
            convertView = LayoutInflater.from(context).inflate(R.layout.fragment_dynamic,null);
            viewHolder = new ViewHolder();
            viewHolder.tv_name = convertView.findViewById(R.id.et_nickname);
            viewHolder.iv_head = convertView.findViewById(R.id.iv_head);
            convertView.setTag(viewHolder);//保存控件


        }

        else
            viewHolder = (ViewHolder) convertView.getTag();//取出控件
//        TextView tv_name = converView.findViewById(R.id.tv_name);
//        ImageView iv_head = converView.findViewById(R.id.iv_head);
        viewHolder.tv_name.setText(data.get(position).getName());
       viewHolder. iv_head.setImageResource(data.get(position).getHeadImage());
        return convertView;
    }

    private class ViewHolder{
        TextView tv_name;
        ImageView iv_head;
    }
}
