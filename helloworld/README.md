Hello world
=
考虑寻找函数最小值问题，给一个如下函数
$$
\frac{1}{2}(x-10)^{2}
$$


稍微有点数学常识的人都知道，当x=10时函数取得最小值，但是作为入门ceres我们可以利用ceres来计算这个值，演示一下ceres的基本用法。

第一步构造一个函数$f(x) = 10 - x$
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

