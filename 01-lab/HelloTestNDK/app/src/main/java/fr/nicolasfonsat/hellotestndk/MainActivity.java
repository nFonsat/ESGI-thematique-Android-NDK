package fr.nicolasfonsat.hellotestndk;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Date;
import java.util.Locale;

public class MainActivity extends Activity implements View.OnClickListener{

    TextView tv_fibonnaci_native;
    TextView tv_fibonnaci_java;
    TextView tv_fibonnaci_callback;

    EditText text;
    Button btn;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv_fibonnaci_native= (TextView) findViewById(R.id.fibonnaci_native);
        tv_fibonnaci_java= (TextView) findViewById(R.id.fibonnaci_java);
        tv_fibonnaci_callback= (TextView) findViewById(R.id.fibonnaci_callback);

        text = (EditText)findViewById(R.id.editText);
        btn = (Button) findViewById(R.id.button);
        btn.setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int fibonnaciC(int n);

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int fibonnaciCallback(int n);


    private int fibonnaciJava(int n) {
        if (n<=1) return 1;
        return (fibonnaciJava(n-1))+(fibonnaciJava(n-2));
    }


    public void onClick(View v) {

        Integer nb = Integer.parseInt(text.getText().toString());

        Date t1Begin = new Date();
        fibonnaciC(nb);
        Date t1End = new Date();

        String timeC = String.format(Locale.getDefault(), "Native speed : %d ms", t1End.getTime() - t1Begin.getTime());
        tv_fibonnaci_native.setText(timeC);
        Log.d("XXXXXX", timeC);

        Date t2Begin = new Date();
        fibonnaciJava(nb);
        Date t2End = new Date();

        String timeJAVA = String.format(Locale.getDefault(), "Java speed : %d ms", (t2End.getTime() - t2Begin.getTime()));
        tv_fibonnaci_java.setText(timeJAVA);
        Log.d("XXXXXX", timeJAVA);

        Date t3Begin = new Date();
        fibonnaciCallback(nb);
        Date t3End = new Date();

        String timeCallback = String.format(Locale.getDefault(), "C/callback speed : %d ms", (t3End.getTime() - t3Begin.getTime()));
        tv_fibonnaci_callback.setText(timeCallback);
        Log.d("XXXXXX", timeCallback);
    }


    public void fibonnaciCallbackC(int n) {
        fibonnaciJava(n);
    }


}
