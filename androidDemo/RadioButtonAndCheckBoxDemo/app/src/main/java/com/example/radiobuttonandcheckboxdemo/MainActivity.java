package com.example.radiobuttonandcheckboxdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.RadioGroup;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private boolean isMale=true;
    private boolean isCheckedLeo = false;
    private boolean isCheckedmob = false;
    private boolean isCheckedAvilio = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //获取性别
        RadioGroup radioGroup = findViewById(R.id.rg_sex);
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if(checkedId == R.id.rb_male)
                    isMale = true;
                else
                    isMale = false;
            }
        });

        //获取墙头数据，注意每个checkbox都要设置相应的侦听器
        CheckBox cb_leo =findViewById(R.id.cb_leo);
        CheckBox cb_mob =findViewById(R.id.cb_mob);
        CheckBox cb_avilio =findViewById(R.id.cb_avilio);
        //多个都要写，太冗余，->在onClick方法外面写,现在这里面写出来，自动出来后，复制粘贴过来
        cb_leo.setOnCheckedChangeListener(onCheckedChangeListener);
        cb_mob.setOnCheckedChangeListener(onCheckedChangeListener);
        cb_avilio.setOnCheckedChangeListener(onCheckedChangeListener);
    }

    private CompoundButton.OnCheckedChangeListener onCheckedChangeListener = new CompoundButton.OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            //先判断哪一个checkbox的状态被改变
            if (buttonView.getId() == R.id.cb_leo)
                isCheckedLeo = isChecked;
            else if (buttonView.getId() == R.id.cb_mob)
                isCheckedmob = isChecked;
            else
                isCheckedAvilio = isChecked;
        }
    };
    //注册处理代码
    public void onClick(View v){
        String result = "sign successifully!";
        result +="\nSex: ";
        if (isMale)
            result += "A";
        else
            result += "O";
        result += "\nFavorite: ";
        if (isCheckedLeo)
            result += "Leo ";
        if (isCheckedmob)
            result += "mob ";
        if (isCheckedAvilio)
            result += "Avilio ";
        Toast.makeText(this,result,Toast.LENGTH_SHORT).show();
    }
}
