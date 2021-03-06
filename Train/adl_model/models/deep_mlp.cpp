// Auto generated by utensor-cli

#include "deep_mlp.hpp"
#include "uTensor/ops/ArrayOps.hpp"
#include "uTensor/ops/MathOps.hpp"
#include "uTensor/core/tensor.hpp"
#include "uTensor/ops/MatrixOps.hpp"
#include "uTensor/core/context.hpp"
#include "uTensor/ops/NnOps.hpp"
#include "uTensor/loaders/tensorIdxImporter.hpp"


void get_deep_mlp_ctx(Context& ctx, Tensor* input_0) {

{ // add tensor for placeholders
    ctx.add(input_0, "x:0", 2);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/MatMul_eightbit_x_reshape_dims_0.idx"),
            "MatMul_eightbit/x/reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "MatMul_eightbit/x/reshape:0", 2);
    ctx.push(new ReshapeOp(), 
             { "x:0", "MatMul_eightbit/x/reshape_dims:0" },
             { "MatMul_eightbit/x/reshape:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/MatMul_eightbit_x_reduction_dims_0.idx"),
            "MatMul_eightbit/x/reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "MatMul_eightbit/x/min:0", 1);
    ctx.push(new MinOp(), 
             { "MatMul_eightbit/x/reshape:0", "MatMul_eightbit/x/reduction_dims:0" },
             { "MatMul_eightbit/x/min:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "MatMul_eightbit/x/max:0", 1);
    ctx.push(new MaxOp(), 
             { "MatMul_eightbit/x/reshape:0", "MatMul_eightbit/x/reduction_dims:0" },
             { "MatMul_eightbit/x/max:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "MatMul_eightbit/x/quantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_eightbit/x/quantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_eightbit/x/quantize:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "x:0",  "MatMul_eightbit/x/min:0", "MatMul_eightbit/x/max:0" },
             {  "MatMul_eightbit/x/quantize:0",  "MatMul_eightbit/x/quantize:1", "MatMul_eightbit/x/quantize:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/constants/deep_mlp/Variable_quantized_const_0.idx"),
            "Variable_quantized_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_quantized_min_0.idx"),
            "Variable_quantized_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_quantized_max_0.idx"),
            "Variable_quantized_max:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "MatMul/eightbit:0", 2);
    ctx.add(new RamTensor<float>({1}), "MatMul/eightbit:1", 2);
    ctx.add(new RamTensor<float>({1}), "MatMul/eightbit:2", 2);
    ctx.push(new QntMatMulOp<uint8_t, uint8_t, int>(), 
             { "MatMul_eightbit/x/quantize:0", "MatMul_eightbit/x/quantize:1", "MatMul_eightbit/x/quantize:2", "Variable_quantized_const:0", "Variable_quantized_min:0",  "Variable_quantized_max:0" },
             { "MatMul/eightbit:0", "MatMul/eightbit:1",  "MatMul/eightbit:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "MatMul/eightbit/requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul/eightbit/requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "MatMul/eightbit:0", "MatMul/eightbit:1", "MatMul/eightbit:2" },
             { "MatMul/eightbit/requant_range:0", "MatMul/eightbit/requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "MatMul/eightbit/requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul/eightbit/requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul/eightbit/requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "MatMul/eightbit:0", "MatMul/eightbit:1", "MatMul/eightbit:2", "MatMul/eightbit/requant_range:0", "MatMul/eightbit/requant_range:1" },
             { "MatMul/eightbit/requantize:0", "MatMul/eightbit/requantize:1", "MatMul/eightbit/requantize:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_1_0.idx"),
            "Variable_1:0",
            2);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/zscore_eightbit_Variable_1_reshape_dims_0.idx"),
            "zscore_eightbit/Variable_1/reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "zscore_eightbit/Variable_1/reshape:0", 2);
    ctx.push(new ReshapeOp(), 
             { "Variable_1:0", "zscore_eightbit/Variable_1/reshape_dims:0" },
             { "zscore_eightbit/Variable_1/reshape:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/zscore_eightbit_Variable_1_reduction_dims_0.idx"),
            "zscore_eightbit/Variable_1/reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "zscore_eightbit/Variable_1/min:0", 1);
    ctx.push(new MinOp(), 
             { "zscore_eightbit/Variable_1/reshape:0", "zscore_eightbit/Variable_1/reduction_dims:0" },
             { "zscore_eightbit/Variable_1/min:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "zscore_eightbit/Variable_1/max:0", 1);
    ctx.push(new MaxOp(), 
             { "zscore_eightbit/Variable_1/reshape:0", "zscore_eightbit/Variable_1/reduction_dims:0" },
             { "zscore_eightbit/Variable_1/max:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "zscore_eightbit/Variable_1/quantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_eightbit/Variable_1/quantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_eightbit/Variable_1/quantize:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "Variable_1:0",  "zscore_eightbit/Variable_1/min:0", "zscore_eightbit/Variable_1/max:0" },
             {  "zscore_eightbit/Variable_1/quantize:0",  "zscore_eightbit/Variable_1/quantize:1", "zscore_eightbit/Variable_1/quantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<int>(), "zscore/eightbit:0", 2);
    ctx.add(new RamTensor<float>({1}), "zscore/eightbit:1", 2);
    ctx.add(new RamTensor<float>({1}), "zscore/eightbit:2", 2);
    ctx.push(new QuantizedAddOp<uint8_t, uint8_t, int>(), 
             { "MatMul/eightbit/requantize:0", "MatMul/eightbit/requantize:1", "MatMul/eightbit/requantize:2", "zscore_eightbit/Variable_1/quantize:0", "zscore_eightbit/Variable_1/quantize:1",  "zscore_eightbit/Variable_1/quantize:2" },
             { "zscore/eightbit:0", "zscore/eightbit:1",  "zscore/eightbit:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "zscore/eightbit/requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "zscore/eightbit/requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "zscore/eightbit:0", "zscore/eightbit:1", "zscore/eightbit:2" },
             { "zscore/eightbit/requant_range:0", "zscore/eightbit/requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "zscore/eightbit/requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "zscore/eightbit/requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "zscore/eightbit/requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "zscore/eightbit:0", "zscore/eightbit:1", "zscore/eightbit:2", "zscore/eightbit/requant_range:0", "zscore/eightbit/requant_range:1" },
             { "zscore/eightbit/requantize:0", "zscore/eightbit/requantize:1", "zscore/eightbit/requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Relu/eightbit:0", 1);
    ctx.add(new RamTensor<float>({1}), "Relu/eightbit:1", 1);
    ctx.add(new RamTensor<float>({1}), "Relu/eightbit:2", 1);
    ctx.push(new ReluOp<uint8_t, float, uint8_t>(), 
             { "zscore/eightbit/requantize:0", "zscore/eightbit/requantize:1", "zscore/eightbit/requantize:2" },
             { "Relu/eightbit:0", "Relu/eightbit:1", "Relu/eightbit:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/constants/deep_mlp/Variable_2_quantized_const_0.idx"),
            "Variable_2_quantized_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_2_quantized_min_0.idx"),
            "Variable_2_quantized_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_2_quantized_max_0.idx"),
            "Variable_2_quantized_max:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "MatMul_1/eightbit:0", 2);
    ctx.add(new RamTensor<float>({1}), "MatMul_1/eightbit:1", 2);
    ctx.add(new RamTensor<float>({1}), "MatMul_1/eightbit:2", 2);
    ctx.push(new QntMatMulOp<uint8_t, uint8_t, int>(), 
             { "Relu/eightbit:0", "Relu/eightbit:1", "Relu/eightbit:2", "Variable_2_quantized_const:0", "Variable_2_quantized_min:0",  "Variable_2_quantized_max:0" },
             { "MatMul_1/eightbit:0", "MatMul_1/eightbit:1",  "MatMul_1/eightbit:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "MatMul_1/eightbit/requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_1/eightbit/requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "MatMul_1/eightbit:0", "MatMul_1/eightbit:1", "MatMul_1/eightbit:2" },
             { "MatMul_1/eightbit/requant_range:0", "MatMul_1/eightbit/requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "MatMul_1/eightbit/requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_1/eightbit/requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_1/eightbit/requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "MatMul_1/eightbit:0", "MatMul_1/eightbit:1", "MatMul_1/eightbit:2", "MatMul_1/eightbit/requant_range:0", "MatMul_1/eightbit/requant_range:1" },
             { "MatMul_1/eightbit/requantize:0", "MatMul_1/eightbit/requantize:1", "MatMul_1/eightbit/requantize:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_3_0.idx"),
            "Variable_3:0",
            2);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/zscore_1_eightbit_Variable_3_reshape_dims_0.idx"),
            "zscore_1_eightbit/Variable_3/reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "zscore_1_eightbit/Variable_3/reshape:0", 2);
    ctx.push(new ReshapeOp(), 
             { "Variable_3:0", "zscore_1_eightbit/Variable_3/reshape_dims:0" },
             { "zscore_1_eightbit/Variable_3/reshape:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/zscore_1_eightbit_Variable_3_reduction_dims_0.idx"),
            "zscore_1_eightbit/Variable_3/reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "zscore_1_eightbit/Variable_3/min:0", 1);
    ctx.push(new MinOp(), 
             { "zscore_1_eightbit/Variable_3/reshape:0", "zscore_1_eightbit/Variable_3/reduction_dims:0" },
             { "zscore_1_eightbit/Variable_3/min:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "zscore_1_eightbit/Variable_3/max:0", 1);
    ctx.push(new MaxOp(), 
             { "zscore_1_eightbit/Variable_3/reshape:0", "zscore_1_eightbit/Variable_3/reduction_dims:0" },
             { "zscore_1_eightbit/Variable_3/max:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "zscore_1_eightbit/Variable_3/quantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_1_eightbit/Variable_3/quantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_1_eightbit/Variable_3/quantize:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "Variable_3:0",  "zscore_1_eightbit/Variable_3/min:0", "zscore_1_eightbit/Variable_3/max:0" },
             {  "zscore_1_eightbit/Variable_3/quantize:0",  "zscore_1_eightbit/Variable_3/quantize:1", "zscore_1_eightbit/Variable_3/quantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<int>(), "zscore_1/eightbit:0", 2);
    ctx.add(new RamTensor<float>({1}), "zscore_1/eightbit:1", 2);
    ctx.add(new RamTensor<float>({1}), "zscore_1/eightbit:2", 2);
    ctx.push(new QuantizedAddOp<uint8_t, uint8_t, int>(), 
             { "MatMul_1/eightbit/requantize:0", "MatMul_1/eightbit/requantize:1", "MatMul_1/eightbit/requantize:2", "zscore_1_eightbit/Variable_3/quantize:0", "zscore_1_eightbit/Variable_3/quantize:1",  "zscore_1_eightbit/Variable_3/quantize:2" },
             { "zscore_1/eightbit:0", "zscore_1/eightbit:1",  "zscore_1/eightbit:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "zscore_1/eightbit/requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_1/eightbit/requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "zscore_1/eightbit:0", "zscore_1/eightbit:1", "zscore_1/eightbit:2" },
             { "zscore_1/eightbit/requant_range:0", "zscore_1/eightbit/requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "zscore_1/eightbit/requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_1/eightbit/requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "zscore_1/eightbit/requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "zscore_1/eightbit:0", "zscore_1/eightbit:1", "zscore_1/eightbit:2", "zscore_1/eightbit/requant_range:0", "zscore_1/eightbit/requant_range:1" },
             { "zscore_1/eightbit/requantize:0", "zscore_1/eightbit/requantize:1", "zscore_1/eightbit/requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "Relu_1/eightbit:0", 1);
    ctx.add(new RamTensor<float>({1}), "Relu_1/eightbit:1", 1);
    ctx.add(new RamTensor<float>({1}), "Relu_1/eightbit:2", 1);
    ctx.push(new ReluOp<uint8_t, float, uint8_t>(), 
             { "zscore_1/eightbit/requantize:0", "zscore_1/eightbit/requantize:1", "zscore_1/eightbit/requantize:2" },
             { "Relu_1/eightbit:0", "Relu_1/eightbit:1", "Relu_1/eightbit:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_4_0.idx"),
            "Variable_4:0",
            2);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/MatMul_2_eightbit_Variable_4_reshape_dims_0.idx"),
            "MatMul_2_eightbit/Variable_4/reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "MatMul_2_eightbit/Variable_4/reshape:0", 2);
    ctx.push(new ReshapeOp(), 
             { "Variable_4:0", "MatMul_2_eightbit/Variable_4/reshape_dims:0" },
             { "MatMul_2_eightbit/Variable_4/reshape:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/MatMul_2_eightbit_Variable_4_reduction_dims_0.idx"),
            "MatMul_2_eightbit/Variable_4/reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "MatMul_2_eightbit/Variable_4/min:0", 1);
    ctx.push(new MinOp(), 
             { "MatMul_2_eightbit/Variable_4/reshape:0", "MatMul_2_eightbit/Variable_4/reduction_dims:0" },
             { "MatMul_2_eightbit/Variable_4/min:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "MatMul_2_eightbit/Variable_4/max:0", 1);
    ctx.push(new MaxOp(), 
             { "MatMul_2_eightbit/Variable_4/reshape:0", "MatMul_2_eightbit/Variable_4/reduction_dims:0" },
             { "MatMul_2_eightbit/Variable_4/max:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "MatMul_2_eightbit/Variable_4/quantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_2_eightbit/Variable_4/quantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_2_eightbit/Variable_4/quantize:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "Variable_4:0",  "MatMul_2_eightbit/Variable_4/min:0", "MatMul_2_eightbit/Variable_4/max:0" },
             {  "MatMul_2_eightbit/Variable_4/quantize:0",  "MatMul_2_eightbit/Variable_4/quantize:1", "MatMul_2_eightbit/Variable_4/quantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<int>(), "MatMul_2/eightbit:0", 2);
    ctx.add(new RamTensor<float>({1}), "MatMul_2/eightbit:1", 2);
    ctx.add(new RamTensor<float>({1}), "MatMul_2/eightbit:2", 2);
    ctx.push(new QntMatMulOp<uint8_t, uint8_t, int>(), 
             { "Relu_1/eightbit:0", "Relu_1/eightbit:1", "Relu_1/eightbit:2", "MatMul_2_eightbit/Variable_4/quantize:0", "MatMul_2_eightbit/Variable_4/quantize:1",  "MatMul_2_eightbit/Variable_4/quantize:2" },
             { "MatMul_2/eightbit:0", "MatMul_2/eightbit:1",  "MatMul_2/eightbit:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "MatMul_2/eightbit/requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_2/eightbit/requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "MatMul_2/eightbit:0", "MatMul_2/eightbit:1", "MatMul_2/eightbit:2" },
             { "MatMul_2/eightbit/requant_range:0", "MatMul_2/eightbit/requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "MatMul_2/eightbit/requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_2/eightbit/requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "MatMul_2/eightbit/requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "MatMul_2/eightbit:0", "MatMul_2/eightbit:1", "MatMul_2/eightbit:2", "MatMul_2/eightbit/requant_range:0", "MatMul_2/eightbit/requant_range:1" },
             { "MatMul_2/eightbit/requantize:0", "MatMul_2/eightbit/requantize:1", "MatMul_2/eightbit/requantize:2" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/constants/deep_mlp/Variable_5_0.idx"),
            "Variable_5:0",
            2);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/logits_eightbit_Variable_5_reshape_dims_0.idx"),
            "logits_eightbit/Variable_5/reshape_dims:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "logits_eightbit/Variable_5/reshape:0", 2);
    ctx.push(new ReshapeOp(), 
             { "Variable_5:0", "logits_eightbit/Variable_5/reshape_dims:0" },
             { "logits_eightbit/Variable_5/reshape:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/logits_eightbit_Variable_5_reduction_dims_0.idx"),
            "logits_eightbit/Variable_5/reduction_dims:0",
            2);
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "logits_eightbit/Variable_5/min:0", 1);
    ctx.push(new MinOp(), 
             { "logits_eightbit/Variable_5/reshape:0", "logits_eightbit/Variable_5/reduction_dims:0" },
             { "logits_eightbit/Variable_5/min:0" });
    ctx.eval();
}
{   
    RamTensor<float>* out_tensor;
    out_tensor = new RamTensor<float>({ 1 });
    ctx.add(out_tensor, "logits_eightbit/Variable_5/max:0", 1);
    ctx.push(new MaxOp(), 
             { "logits_eightbit/Variable_5/reshape:0", "logits_eightbit/Variable_5/reduction_dims:0" },
             { "logits_eightbit/Variable_5/max:0" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "logits_eightbit/Variable_5/quantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "logits_eightbit/Variable_5/quantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "logits_eightbit/Variable_5/quantize:2", 1);
    ctx.push(new QuantizeV2Op(),
             {  "Variable_5:0",  "logits_eightbit/Variable_5/min:0", "logits_eightbit/Variable_5/max:0" },
             {  "logits_eightbit/Variable_5/quantize:0",  "logits_eightbit/Variable_5/quantize:1", "logits_eightbit/Variable_5/quantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<int>(), "logits/eightbit:0", 2);
    ctx.add(new RamTensor<float>({1}), "logits/eightbit:1", 2);
    ctx.add(new RamTensor<float>({1}), "logits/eightbit:2", 2);
    ctx.push(new QuantizedAddOp<uint8_t, uint8_t, int>(), 
             { "MatMul_2/eightbit/requantize:0", "MatMul_2/eightbit/requantize:1", "MatMul_2/eightbit/requantize:2", "logits_eightbit/Variable_5/quantize:0", "logits_eightbit/Variable_5/quantize:1",  "logits_eightbit/Variable_5/quantize:2" },
             { "logits/eightbit:0", "logits/eightbit:1",  "logits/eightbit:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "logits/eightbit/requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "logits/eightbit/requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "logits/eightbit:0", "logits/eightbit:1", "logits/eightbit:2" },
             { "logits/eightbit/requant_range:0", "logits/eightbit/requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "logits/eightbit/requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "logits/eightbit/requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "logits/eightbit/requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "logits/eightbit:0", "logits/eightbit:1", "logits/eightbit:2", "logits/eightbit/requant_range:0", "logits/eightbit/requant_range:1" },
             { "logits/eightbit/requantize:0", "logits/eightbit/requantize:1", "logits/eightbit/requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>(), "logits:0", 1);
    ctx.push(new DequantizeOp(), 
             { "logits/eightbit/requantize:0", "logits/eightbit/requantize:1", "logits/eightbit/requantize:2" },
             { "logits:0" });
    ctx.eval();
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.int_import("/fs/constants/deep_mlp/y_pred_dimension_0.idx"),
            "y_pred/dimension:0",
            1);
}
{
    ctx.add(new RamTensor<int>(), "y_pred:0");
    ctx.push(new ArgMaxOp<float, int>(), 
             { "logits:0", "y_pred/dimension:0" },
             { "y_pred:0" });
}
}