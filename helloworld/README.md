Hello world
=
考虑寻找函数最小值问题，给一个如下函数
```math
\frac{1}{2}(x-10)^{2}
```


稍微有点数学常识的人都知道，当x=10时函数取得最小值，但是作为入门ceres我们可以利用ceres来计算这个值，演示一下ceres的基本用法。

第一步构造一个函数$f(x) = 10 - x $
实现一个结构体
```
struct CostFunctor{
    template<typename T>
    bool operator()(const T *const x , T * residual) const {
        residual[0] = T(10.0) - x[0];
        return true;
    }
}
```
定义完残差函数，我们可以用ceres构造一个非线性最小二乘问题解决它。

```
int main()
{
    cout << "Hello World!" << endl;
    // 定义一个初始值
    double init_val = 5.0;
    double x = init_val;

    // build the problem
    ceres::Problem problem;
    ceres::CostFunction *cost_function = new ceres::AutoDiffCostFunction<CostFunctor , 1 , 1>(new CostFunctor);
    problem.AddResidualBlock(cost_function , NULL , &x);

    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = true;
    ceres::Solver::Summary summary;
    ceres::Solve(options , &problem , &summary);

    std::cout << summary.BriefReport() << "\n";
    std::cout << "x : " << init_val
              << " -> " << x << "\n";
    return 0;
}
```

ceres::AutoDiffCostFunction  自动求导
编译并打印结果
iter      cost      cost_change  |gradient|   |step|    tr_ratio  tr_radius  ls_iter  iter_time  total_time
   0  1.250000e+01    0.00e+00    5.00e+00   0.00e+00   0.00e+00  1.00e+04        0    5.01e-05    3.54e-03
   1  1.249750e-07    1.25e+01    5.00e-04   5.00e+00   1.00e+00  3.00e+04        1    5.98e-04    4.20e-03
   2  1.388518e-16    1.25e-07    1.67e-08   5.00e-04   1.00e+00  9.00e+04        1    5.96e-06    4.22e-03
Ceres Solver Report: Iterations: 3, Initial cost: 1.250000e+01, Final cost: 1.388518e-16, Termination: CONVERGENCE
x : 5 -> 10
