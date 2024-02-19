# 项目层次划分

1. **Event**
2. Provider
3. Model
4. **Rule**
5. Controller

`Provider` 提供所有功能的根本实现. `Model` 表示一种便利的模型, 允许方便的操作 `Provider` 提供的接口和常见的操作模
式. `Controller` 控制整个过程, 并提供一些本地功能 (比如计时器). `Rule` 是一组事件驱动的规则, 使用 Composite 模式
构建.上述顺序表示组件间的可见性, 序号小的组件不可见序号大的组件. 

# 接口重调

为了在不具有Qt环境下进行开发扩展，Event组件和Rule组件的上层接口上不与Qt耦合。

- [ ] Event接口重调
- [ ] Rule接口重调

# 基本实现

- [ ] WSSController
- [ ] WSSProvider
- [ ] Events
- [ ] Rules