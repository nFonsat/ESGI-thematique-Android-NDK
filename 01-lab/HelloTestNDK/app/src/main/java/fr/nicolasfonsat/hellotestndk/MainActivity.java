package fr.nicolasfonsat.hellotestndk;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.Date;
import java.util.Locale;

public class MainActivity extends Activity {

    private final static int CONSTANT = 30;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        TextView tv_fibonnaci_native= (TextView) findViewById(R.id.fibonnaci_native);
        TextView tv_fibonnaci_java= (TextView) findViewById(R.id.fibonnaci_java);
        TextView tv_fibonnaci_callback= (TextView) findViewById(R.id.fibonnaci_callback);

        Date t1Begin = new Date();
        fibonnaciC(CONSTANT);
        Date t1End = new Date();

        String timeC = String.format(Locale.getDefault(), "Fibonnaci native : %d ms", t1End.getTime() - t1Begin.getTime());
        tv_fibonnaci_native.setText(timeC);
        Log.d("XXXXXX", timeC);

        Date t2Begin = new Date();
        fibonnaciJava(CONSTANT);
        Date t2End = new Date();

        String timeJAVA = String.format(Locale.getDefault(), "Fibonnaci java : %d ms", (t2End.getTime() - t2Begin.getTime()));
        tv_fibonnaci_java.setText(timeJAVA);
        Log.d("XXXXXX", timeJAVA);

        Date t3Begin = new Date();
        fibonnaciCallback(CONSTANT);
        Date t3End = new Date();

        String timeCallback = String.format(Locale.getDefault(), "Fibonnaci callback : %d ms", (t3End.getTime() - t3Begin.getTime()));
        tv_fibonnaci_callback.setText(timeCallback);
        Log.d("XXXXXX", timeCallback);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

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

    public void fibonnaciCallbackC(int n) {
        fibonnaciJava(n);
    }


}
