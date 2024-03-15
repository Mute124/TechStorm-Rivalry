using System.Numerics;
using System.Runtime.ConstrainedExecution;
using Raylib_cs;

namespace TechStormDevTool.Core.UI {
    class UIContainer {
        public Vector2 containerAnchor;
        public UIContainer containerMother;
        private List<UIElement> containerChildren;

        public void UpdateChildren() {
            for (int i = 0; i < containerChildren.Count; i++) {
                containerChildren[i].Update();
            }
        }

        public virtual void Update() {}

        public void Draw() {
            for (int i = 0; i < containerChildren.Count; i++) {
                containerChildren[i].Draw();
            }
        }

        public virtual void OnDraw() {}

    }

    // mother of all containers
    class UIMother : UIContainer {
        public List<UIContainer> children;

        void CreateChild(UIContainer container) {
            container.containerMother = this;
            container.containerAnchor = this.containerAnchor;
            children.Add(container);
        }

        void Update() {
            for(int i = 0; i < children.Count(); i++) {
                children[i].UpdateChildren();
            }
        }
    }



}