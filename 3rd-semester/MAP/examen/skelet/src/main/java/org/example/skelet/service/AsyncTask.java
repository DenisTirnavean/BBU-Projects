package org.example.skelet.service;


public class AsyncTask <E extends Service> extends Thread{
    E service;
    public AsyncTask (E service){
        this.service = service;
    }


    @Override
    public void run() {
        super.run();
    }
}
