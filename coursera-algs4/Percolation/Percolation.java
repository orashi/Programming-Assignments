import edu.princeton.cs.algs4.WeightedQuickUnionUF;
public class Percolation {
    private short [][] grid;
    private final int D;
    private WeightedQuickUnionUF uni,seunl;
    public Percolation(int N)               // create N-by-N grid, with all sites blocked
    {
        if (N <= 0)
            throw new IllegalArgumentException();
        else
        {   
            D = N;
            grid = new short [N+2][N+2];
            uni = new WeightedQuickUnionUF(N*N+2);
            seunl = new WeightedQuickUnionUF(N*N+1);
        }   
    }
    public void open(int i, int j)          // open site (row i, column j) if it is not open already
    {
        check(i, j);
        if (grid[i][j] == 0)
            grid[i][j] = 1;
        if (i == 1 && j > 0 && j <= D)
        {
            uni.union(convert(i, j), D*D);
            seunl.union(convert(i, j), D*D);
            linka(i, j);
        }
        else if (i == D && j > 0 && j <= D)
        {
            uni.union(convert(i, j), D*D+1);
            linka(i, j);
        }
        else
            linka(i, j);
    }
    
    public boolean isOpen(int i, int j)     // is site (row i, column j) open?
    {
        check(i, j);
        return grid[i][j] == 1;
    }
    public boolean isFull(int i, int j)     // is site (row i, column j) full?
    {
        check(i, j);
        return seunl.connected(convert(i, j), D*D);
    }
    public boolean percolates()             // does the system percolate?
    {
        return uni.connected(D*D+1, D*D);
    }
    
    private int convert(int i,int j)
    {
        return D*(i-1)+j-1;
    }
    private void linka(int i,int j)
    {
        if ( i-1 > 0 && i-1 <= D && j > 0 && j <= D && isOpen(i-1, j))
        {
            uni.union(convert(i-1, j), convert(i, j));
            seunl.union(convert(i-1, j), convert(i, j));
        }  
        if (i+1 > 0 && i+1 <= D && j > 0 && j <= D && isOpen(i+1, j))
        {
            uni.union(convert(i+1, j), convert(i, j));
            seunl.union(convert(i+1, j), convert(i, j));
        } 
        if (i > 0 && i <= D && j-1 > 0 && j-1 <= D && isOpen(i, j-1))
        {
            uni.union(convert(i, j-1), convert(i, j));
            seunl.union(convert(i, j-1), convert(i, j));
        } 
        if (i > 0 && i <= D && j+1 > 0 && j+1 <= D && isOpen(i, j+1))
        {
            uni.union(convert(i, j+1), convert(i, j));
            seunl.union(convert(i, j+1), convert(i, j));
        }
    }
    private void check(int i,int j)
    {
        if (i <= 0 || i > D || j <= 0 || j > D)
            throw new IndexOutOfBoundsException();
    }
}
