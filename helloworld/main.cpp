#include <iostream>
#include <ceres/ceres.h>


using namespace std;

// 首先定义一个损失函数
struct CostFunctor{
    template<typename T>
    bool operator()(const T *const x , T * residual) const {
        residual[0] = T(10.0) - x[0];
        return true;
    }
};

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
