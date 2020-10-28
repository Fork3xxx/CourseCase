package com.example.listview_chatdemo;

public class Message {
    private String content;
    private boolean isSend;     //用来表示消息类型，如果为true，则消息为发送；否则为接收

    public Message(String content, boolean isSend) {
        this.content = content;
        this.isSend = isSend;
    }

    public String getContent() {
        return content;
    }


    public boolean isSend() {
        return isSend;
    }


}
