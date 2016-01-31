import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.StdOut;
public class PercolationStats {
    
    private double t;
    private double []adds;
    public PercolationStats(int N, int T)     // perform T independent experiments on an N-by-N grid
    {
        if (N <= 0 || T <= 0)
            throw new IllegalArgumentException();
        t = T;
        Percolation per = new Percolation(N);
        int a, b, add = 0;
        adds = new double[T];
        while(T != 0)
        {
            a = StdRandom.uniform(N) + 1;
            b = StdRandom.uniform(N) + 1;
            if (!per.isOpen(a, b))
            {
                per.open(a, b);
                add++;
            }
            if (per.percolates())
            {
                T--;
                adds[T] = (add+0.0)/(N*N);
                add = 0;
                if (T != 0)
                    per = new Percolation(N);
            }
        }
    }
    public double mean()     
    {
        return StdStats.mean(adds);
    }                 // sample mean of percolation threshold
    public double stddev()      
    {
        return StdStats.stddev(adds);
    }              // sample standard deviation of percolation threshold
    public double confidenceLo()   
    {
        return mean()-(1.96*stddev())/Math.sqrt(t);
    }           // low  endpoint of 95% confidence interval
    public double confidenceHi() 
    {
        return mean()+(1.96*stddev())/Math.sqrt(t);
    }  // high endpoint of 95% confidence interval
    public static void main(String[] args) 
    {
        int N = Integer.parseInt(args[0]);
        int T = Integer.parseInt(args[1]);
        PercolationStats stats = new PercolationStats(N, T);
        StdOut.printf("mean                    = %.7f\n",stats.mean());
        StdOut.printf("stddev                  = %.15f\n",stats.stddev());
        StdOut.printf("95%% confidence interval = %.15f, %.15f\n",stats.confidenceLo(),stats.confidenceHi());
    }   // test client 
}
