package com.example.owno;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class MessageAdapter extends BaseAdapter {
    private ArrayList<Message> data;
    private Context context;

    public MessageAdapter(ArrayList<Message>data, Context context){
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
        if (convertView == null || data.get(position).isSend()!= ((ViewHolder)convertView.getTag()).isSend){

            if (data.get(position).isSend())
                //发消息
                 convertView = LayoutInflater.from(context).inflate(R.layout.listview_item_send,null);
            else
                //收消息
                convertView = LayoutInflater.from(context).inflate(R.layout.listview_item_receive,null);
            viewHolder = new ViewHolder();
            viewHolder.tv_content = convertView.findViewById(R.id.tv_content);
            viewHolder.isSend = data.get(position).isSend();
            convertView.setTag(viewHolder);//保存控件


        }

        else
            viewHolder = (ViewHolder) convertView.getTag();//取出控件
//        TextView tv_name = converView.findViewById(R.id.tv_name);
//        ImageView iv_head = converView.findViewById(R.id.iv_head);
        viewHolder.tv_content.setText(data.get(position).getContent());


        return convertView;
    }

    private class ViewHolder{
        boolean isSend;
        TextView tv_content;

}

}
