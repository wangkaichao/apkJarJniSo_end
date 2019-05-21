package com.example.test_shi_application;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.util.Log;
import android.content.Context;
import android.widget.Button;
import android.widget.TextView;

import com.tianci.plugins.factory.BaseGeneralManager;
import com.tianci.plugins.factory.BaseFactoryManager;
import com.tianci.plugins.factory.BaseFactoryManager.OnInitListener;
import com.test.testJar;
import com.jni.testJni;


import java.io.File;

import android.content.Context;

import dalvik.system.DexClassLoader;

public class MainActivity extends Activity {

    private BaseFactoryManager factoryManager = null;
    private BaseGeneralManager generalManager = null;
    private testJar test_jar = null;
    private testJni test_jni = null;
    private static BaseFactoryManager mFactoryManager = null;

    private Context mContext = null;
    private final static String pluginFilePath = "/system/plugins/AtomicFactoryPlugin.jar";
    private final static String pluginClazz = "com.skyworth.factory.FactoryManager";


    public static BaseFactoryManager LoadFactoryManager(Context context)
    {
        if (new File(pluginFilePath).exists())
        {
            DexClassLoader loader = new DexClassLoader(pluginFilePath,
                    context.getDir("dex", 0).getAbsolutePath(), null, context.getClassLoader());
            try
            {
                mFactoryManager = (BaseFactoryManager) loader.loadClass(pluginClazz).newInstance();
                if(mFactoryManager == null)
                {
                    Log.d("LoadFactoryManager","shibo mFactoryManager");
                }

            } catch (InstantiationException e)
            {
                e.printStackTrace();
            } catch (IllegalAccessException e)
            {
                e.printStackTrace();
            } catch (ClassNotFoundException e)
            {
                e.printStackTrace();
            }
        }
        return mFactoryManager;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mContext = this;
        String  textIfo = "";
        test_jar = new testJar();
        textIfo = test_jar.test();
        Log.d("oncreat","shibo textIfo = " + textIfo);
        test_jni = testJni.getInstance();
        Log.d("oncreat","shibo 111111");
        textIfo = test_jni.getInfoFromServer();
        Log.d("oncreat","shibo 222222222");
        factoryManager = LoadFactoryManager(this);
        factoryManager.init(mContext, new OnInitListener(){
            @Override
            public void onInit()
            {
                Log.d("onInit","shibo init");
            }
        });
        if(factoryManager == null)
        {
            Log.d("onCreate","shibo factoryManager");
        }
        generalManager = factoryManager.getGeneralManager();
        if(generalManager == null)
        {
            Log.d("onCreate","shibo generalManager");
        }

        setContentView(R.layout.activity_main);
        TextView textView1=(TextView)findViewById(R.id.textView);
        if (generalManager == null)
        {
            textView1.setText("shibo 1111111222222");
        }
        else
        {
            String barcode = generalManager.getBarcode();
            textView1.setText(textIfo);
        }

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

}
