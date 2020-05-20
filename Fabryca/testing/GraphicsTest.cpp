#include "graphics/Graphics.h"

#include <gtest/gtest.h>
#include <cmath>


TEST(VertexBufferTest, SharedGeometry) {
    Byte* data = new Byte[10];
    VertexBuffer buffer1(data, 10);
    delete[] data;

    VertexBuffer buffer2 = buffer1;

    ASSERT_EQ(buffer1.id(), buffer2.id());
    ASSERT_EQ(buffer1.dataSize(), buffer2.dataSize());
}

TEST(SceneObjectTest, RelativeTransformations) {
    SceneObject parent;
    SceneObject child;

    child.setPosition(1, 2, 3);

    parent.addChild(child);
    ASSERT_EQ(parent.children().size(), 1);
    ASSERT_EQ(child.parent(), &parent);

    parent.setPosition(1, 1, 1);
    ASSERT_EQ(child.position(), glm::vec3(2, 3, 4));
}
