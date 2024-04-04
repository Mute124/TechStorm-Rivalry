<?xml version="1.0" encoding="utf-8"?>
<file>
	<afflictions>
		<affliction>
			<name>Bleeding</name>
			<tooltip>Blood is coming out of the wound!</tooltip>

			<causes>
				<cause>Sharps</cause>
			</causes>
			<treatments>
				<treatment>bandage</treatment>
			</treatments>
			<affects>
				<affect>
					<!--What about the player gets affected?-->
					<targetcomponent>blood</targetcomponent>
					<!--how much should be changed each affliction update?-->
					<changefactor></changefactor>
				</affect>
			</affects>
		</affliction>
	</afflictions>
</file>
