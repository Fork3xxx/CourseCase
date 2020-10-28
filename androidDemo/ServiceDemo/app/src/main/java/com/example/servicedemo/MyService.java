package com.example.servicedemo;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;
import android.util.Log;

public class MyService extends Service {

    MediaPlayer mediaPlayer;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        //创建媒体播放器
        mediaPlayer = MediaPlayer.create(this,R.raw.music);

        Log.i("service","onCreate");
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        int opt = intent.getIntExtra("opt",1);//获取进行播放还是暂停的数据

        if (opt == 1) {
            if (mediaPlayer != null)
                mediaPlayer.start();//播放音乐
        }
        else
            if (mediaPlayer != null)
                mediaPlayer.pause();//暂停播放


        Log.i("service","onStartCommand");
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {

        //停止音乐播放
        if (mediaPlayer != null){
            mediaPlayer.stop();
            mediaPlayer.release();
        }



        Log.i("service","onDestroy");
        super.onDestroy();
    }
}
