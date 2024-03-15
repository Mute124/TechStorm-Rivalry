using System.Numerics;

namespace TechStormDevTool.Core.UI
{
    internal abstract class UIElement
    {
        #region Public Fields

        public Vector2 anchor;

        #endregion Public Fields

        #region Public Methods

        public void Draw()
        {
        }

        public void init(Vector2 anchor)
        {
            this.anchor = anchor;
        }

        public void Update()
        {
        }

        #endregion Public Methods
    }
}
