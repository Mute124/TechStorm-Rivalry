using System.Numerics;
using Raylib_cs;

namespace TechStormDevTool.Core.UI
{
    abstract class UIElement {
        public Vector2 anchor;

        public void init(Vector2 anchor) {
            this.anchor = anchor;
        }
        
        public void Draw() {

        }   


        public void Update() {
            
        }
    }
}
