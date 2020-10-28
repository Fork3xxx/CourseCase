package com.example.progressbar_alertdialog_popupwindow;

import android.content.DialogInterface;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.ColorDrawable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.ProgressBar;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private ProgressBar progressBar;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        progressBar = findViewById(R.id.pb_horizontal);

    }

    //处理界面上三个Button点击事件
    public void onClick(View view){
            //通过button的id区分点击了不同的Button
        if (view.getId()==R.id.btn_addprogress)
            progressBar.setProgress(progressBar.getProgress() + 10);
        else if (view.getId()==R.id.btn_reduceprogress)
            progressBar.setProgress(progressBar.getProgress()- 10);
        else  if (view.getId()==R.id.btn_show_popupwindow)
          //  showAsDropDown();
            showAsDropDown();
        else
            showPopupWindow();
    }
    //用来显示当前位置下面的popupwindow
    private void showAsDropDown(){
        Button btnShowPopupwindow = (Button) findViewById(R.id.btn_show_popupwindow);
        btnShowPopupwindow.setOnClickListener(this);
        View popView =
                LayoutInflater.from(this).inflate(R.layout.popup_drop_down,null);
        //设置PopupWindow View,宽度，高度
        PopupWindow popupWindow=new PopupWindow(popView,LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        popupWindow.setOutsideTouchable(true);//设置允许在外点击消失
        popupWindow.setBackgroundDrawable(new BitmapDrawable());
        popupWindow.showAsDropDown(btnShowPopupwindow,100,0);
    }
    //用来显示底部的popupwindow
    private void  showPopupWindow(){
        View popView = LayoutInflater.from(this).inflate(R.layout.popupwindow_bottom,null);

        final PopupWindow popupWindow = new PopupWindow(popView, LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);
        popupWindow.setOutsideTouchable(true);//设置允许在外点击消失
        popupWindow.setBackgroundDrawable(new ColorDrawable(0x30000000));//设置背景颜色
        //设置显示位置
        //设置动画
        popupWindow.setAnimationStyle(R.style.Animation_Bottom_Dialog);
        popupWindow.showAtLocation(getWindow().getDecorView(),Gravity.BOTTOM,0,0);
        //这里不能直接调用findViewByid找button,因为这里的Button不在MainActivity的布局里面
        Button btn_viewprogress = popView.findViewById(R.id.btn_viewprogress);
        btn_viewprogress.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int progress = progressBar.getProgress();
                Toast.makeText(MainActivity.this,"当前进度值："+progress, Toast.LENGTH_LONG).show();
                popupWindow.dismiss();
            }
        });
        Button btn_closeapp = popView.findViewById(R.id.btn_closeapp);
        btn_closeapp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                popupWindow.dismiss();//关闭popupwindow
                showAlertDialog();//显示是否关闭应用的对话框
            }
        });
    }
    private void showAlertDialog(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("提示");//设置标题
        builder.setMessage("确认退出吗？");//设置消息
        builder.setIcon(R.mipmap.ic_launcher);
        builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                MainActivity.this.finish();//结束当前Acitivity
            }
        });
        builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
        builder.create().show();
    }

    @Override
    public void onPointerCaptureChanged(boolean hasCapture) {

    }
}


